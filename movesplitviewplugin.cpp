/*
* This file is part of KDevelop
*
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
*/

#include "movesplitviewplugin.h"

#include <kpluginfactory.h>
#include <kactioncollection.h>
#include <kaction.h>
#include <klocale.h>
#include <kaboutdata.h>

#include <interfaces/icore.h>
#include <interfaces/iuicontroller.h>
#include <interfaces/idocumentcontroller.h>

#include <sublime/mainwindow.h>
#include <sublime/area.h>
#include <sublime/view.h>
#include <sublime/document.h>

K_PLUGIN_FACTORY(MoveSplitViewFactory, registerPlugin<MoveSplitViewPlugin>();)
K_EXPORT_PLUGIN(MoveSplitViewFactory(KAboutData(
  "kdevmovesplitview",
  "kdevmovesplitview",
  ki18n("MoveSplitView"),
  "0.7",
  ki18n("Move and clean split view"),
  KAboutData::License_GPL
)))

MoveSplitViewPlugin::MoveSplitViewPlugin(QObject *parent, const QVariantList &args)
:KDevelop::IPlugin(MoveSplitViewFactory::componentData(), parent)
{
	Q_UNUSED(args);

	KAction* action;

	action = actionCollection()->addAction("move_previous_split_view");
	action->setText(i18n("Move Split View In Previous Split View"));
	action->setShortcut(Qt::CTRL + Qt::ALT + Qt::Key_Left);
	connect(action, SIGNAL(triggered()), SLOT(moveViewInPreviousArea()));

	action = actionCollection()->addAction("move_next_split_view");
	action->setText(i18n("Move Split View In Next Split View"));
	action->setShortcut(Qt::CTRL + Qt::ALT + Qt::Key_Right);
	connect(action, SIGNAL(triggered()), SLOT(moveViewInNextArea()));

	action = actionCollection()->addAction("copy_previous_split_view");
	action->setText(i18n("Copy Split View In Previous Split View"));
	action->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::ALT + Qt::Key_Left);
	connect(action, SIGNAL(triggered()), SLOT(copyViewInPreviousArea()));

	action = actionCollection()->addAction("copy_next_split_view");
	action->setText(i18n("Copy Split View In Next Split View"));
	action->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::ALT + Qt::Key_Right);
	connect(action, SIGNAL(triggered()), SLOT(copyViewInNextArea()));

	action = actionCollection()->addAction("clean_split_view");
	action->setText(i18n("Clean Split View"));
	connect(action, SIGNAL(triggered()), SLOT(cleanView()));

	action = actionCollection()->addAction("clean_all_split_view");
	action->setText(i18n("Clean All Split View"));
	connect(action, SIGNAL(triggered()), SLOT(cleanAllView()));

	setXMLFile("kdevmovesplitview.rc");
}

struct MoveSplitViewPluginImpl
{
  inline static Sublime::MainWindow* activeMainWindow()
  {
    Sublime::MainWindow* window = qobject_cast<Sublime::MainWindow*>(
      KDevelop::ICore::self()->uiController()->activeMainWindow()
    );

    if (!window || !window->area() || !window->area()->activeView()) {
      return nullptr;
    }
    return window;
  }

  inline static void switcher(bool forward, bool copy)
  {
    Sublime::MainWindow* window = activeMainWindow();
    if (!window) {
      return;
    }

    Sublime::Area* area = window->area();
    Sublime::View* activeView = area->activeView();
    Sublime::AreaIndex* areaindex = area->indexOf(activeView);
    if (areaindex && areaindex->parent()) {
      if (forward) {
        if (areaindex->parent()->second() == areaindex) {
          do {
            areaindex = areaindex->parent();
          } while (areaindex->parent() && areaindex->parent()->second() == areaindex);
          areaindex = areaindex->parent();
          areaindex = areaindex ? areaindex->second() : area->rootIndex();
        } else {
          areaindex = areaindex->parent()->second();
        }
        while (areaindex->isSplit()) {
          areaindex = areaindex->first();
        }
      } else {
        if (areaindex->parent()->first() == areaindex) {
          do {
            areaindex = areaindex->parent();
          } while (areaindex->parent() && areaindex->parent()->first() == areaindex);
          areaindex = areaindex->parent();
          areaindex = areaindex ? areaindex->first() : area->rootIndex();
        } else {
          areaindex = areaindex->parent()->first();
        }
        while (areaindex->isSplit()) {
          areaindex = areaindex->second();
        }
      }

      auto doc_controller = KDevelop::ICore::self()->documentController();
      KDevelop::IDocument* doc = doc_controller->activeDocument();
      if (doc) {
        for (auto view : areaindex->views()) {
          if (view->hasWidget() && view->widget()->isVisible()) {
            window->activateView(view);
            break;
          }
        }
        doc_controller->openDocument(doc);
        if (!copy) {
          delete area->removeView(activeView);
        }
      }
    } else if (areaindex->viewCount() > 1) {
      area->addView(activeView->document()->createView(), activeView, Qt::Horizontal);
      if (!copy) {
        delete area->removeView(activeView);
      }
    }
  }

  inline static void cleanView(bool all)
  {
    Sublime::MainWindow* window = activeMainWindow();
    if (!window) {
      return;
    }

    typedef QList<Sublime::View*> QListView;
    typedef QListView::iterator ListIterator;
    Sublime::Area* area = window->area();
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
};


void MoveSplitViewPlugin::moveViewInNextArea() const
{
	MoveSplitViewPluginImpl::switcher(true, false);
}

void MoveSplitViewPlugin::moveViewInPreviousArea() const
{
	MoveSplitViewPluginImpl::switcher(false, false);
}

void MoveSplitViewPlugin::copyViewInNextArea() const
{
	MoveSplitViewPluginImpl::switcher(true, true);
}

void MoveSplitViewPlugin::copyViewInPreviousArea() const
{
	MoveSplitViewPluginImpl::switcher(false, true);
}

void MoveSplitViewPlugin::cleanAllView() const
{
	MoveSplitViewPluginImpl::cleanView(true);
}

void MoveSplitViewPlugin::cleanView() const
{
	MoveSplitViewPluginImpl::cleanView(false);
}


#include "movesplitviewplugin.moc"
