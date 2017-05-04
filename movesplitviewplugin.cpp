/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* \author Jonathan Poelen <jonathan.poelen@gmail.com>
*/

#include "movesplitviewplugin.h"

#include <kpluginfactory.h>
#include <kactioncollection.h>
#include <klocale.h>
#include <kaboutdata.h>

#include <interfaces/icore.h>
#include <interfaces/iuicontroller.h>
#include <interfaces/idocumentcontroller.h>

#include <sublime/mainwindow.h>
#include <sublime/area.h>
#include <sublime/view.h>
#include <sublime/document.h>


K_PLUGIN_FACTORY_WITH_JSON(MoveSplitViewFactory, "kdevmovesplitview.json", registerPlugin<KDevMoveSplitViewPlugin>();)

namespace
{
  void nextView(bool next, bool copy);
  void cleanView(bool all);
};

KDevMoveSplitViewPlugin::KDevMoveSplitViewPlugin(QObject *parent, const QVariantList &)
:KDevelop::IPlugin(QStringLiteral("kdevmovesplitview"), parent)
{
  setXMLFile(QStringLiteral("kdevmovesplitview.rc"));

  auto ac = actionCollection();
  auto addAction = [ac,this](QString const& name, QString const& icon, char const * desc, auto act){
    QAction* action = ac->addAction(name);
    action->setText(i18n(desc));
    action->setIcon(QIcon::fromTheme(icon));
    connect(action, &QAction::triggered, this, act);
    return action;
  };

  ac->setDefaultShortcut(addAction(
    QStringLiteral("move_previous_split_view"),
    QStringLiteral("arrow-left"),
    "Move Window In Previous Split View",
    []{ nextView(false, false); }
  ), Qt::CTRL + Qt::ALT + Qt::Key_Left);

  ac->setDefaultShortcut(addAction(
    QStringLiteral("move_next_split_view"),
    QStringLiteral("arrow-right"),
    "Move Window In Next Split View",
    []{ nextView(true, false); }
  ), Qt::CTRL + Qt::ALT + Qt::Key_Right);

  ac->setDefaultShortcut(addAction(
    QStringLiteral("copy_previous_split_view"),
    QStringLiteral("arrow-left-double"),
    "Copy Window In Previous Split View",
    []{ nextView(false, true); }
  ), Qt::CTRL + Qt::SHIFT + Qt::ALT + Qt::Key_Left);

  ac->setDefaultShortcut(addAction(
    QStringLiteral("copy_next_split_view"),
    QStringLiteral("arrow-right-double"),
    "Copy Window In Next Split View",
    []{ nextView(true, true); }
  ), Qt::CTRL + Qt::SHIFT + Qt::ALT + Qt::Key_Right);

  addAction(
    QStringLiteral("clean_split_view"),
    QStringLiteral("view-close"),
    "Clean Split View",
    []{ cleanView(false); }
  );

  addAction(
    QStringLiteral("clean_all_split_view"),
    QStringLiteral("view-close"),
    "Clean All Split View",
    []{ cleanView(true); }
  );
}

KDevMoveSplitViewPlugin::~KDevMoveSplitViewPlugin() = default;

#include <kdevplatform/shell/core.h>
#include <kdevplatform/shell/uicontroller.h>
namespace
{
  Sublime::MainWindow* activeMainWindow()
  {
    auto ui = KDevelop::ICore::self()->uiController();
    return ui ? qobject_cast<Sublime::MainWindow*>(ui->activeMainWindow()) : nullptr;
  }

  // inspired by kdevplatform/shell/mainwindow_actions.cpp
  void nextView(bool next, bool copy)
  {
    Sublime::MainWindow* window = activeMainWindow();
    if (!window) {
      return;
    }

    Sublime::Area* area = window->area();
    if (!area) {
      return;
    }

    Sublime::View* activeView = window->activeView();
    if (!activeView) {
      return;
    }

    QList<Sublime::View*> topViews = window->getTopViews();
    if (topViews.count() <= 0) {
      return;
    }

    if (topViews.count() == 1) {
      auto newView = activeView->document()->createView();
      area->addView(newView, activeView, Qt::Horizontal);
      window->activateView(activeView);
    }
    else {
      auto doc_controller = KDevelop::ICore::self()->documentController();
      KDevelop::IDocument* doc = doc_controller->activeDocument();

      if (!doc) {
        return;
      }

      int viewIndex = topViews.indexOf(activeView);
      viewIndex += next ? 1 : -1;

      if (viewIndex < 0) {
        viewIndex = topViews.count() - 1;
      }
      else if (viewIndex >= topViews.count()) {
        viewIndex = 0;
      }

      window->activateView(topViews.at(viewIndex));
      doc_controller->openDocument(doc);
    }

    if (!copy) {
      delete area->removeView(activeView);
    }
  }

  void cleanView(bool all)
  {
    Sublime::MainWindow* window = activeMainWindow();
    if (!window) {
      return;
    }

    Sublime::Area* area = window->area();
    if (!area) {
      return;
    }

    typedef QList<Sublime::View*> QListView;
    typedef QListView::iterator ListIterator;
    QListView views = area->views();
    QListView removed;

    if (all) {
      for (ListIterator it = views.begin(), end = views.end(); it != end; ++it) {
        for (ListIterator it2 = it; ++it2 != end;) {
          if ((*it)->document() == (*it2)->document()) {
            removed.push_front(*it);
            break;
          }
        }
      }
    }
    else {
      for (auto * aview : area->indexOf(area->activeView())->views()) {
        for (auto * view : views) {
          if (view != aview && view->document() == aview->document()) {
            removed.push_front(aview);
            break;
          }
        }
      }
    }

    for (auto * view : removed) {
      delete area->removeView(view);
    }
  }
}

#include "movesplitviewplugin.moc"
