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

#include "switchviewerplugin.h"

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

K_PLUGIN_FACTORY(SwitchViewerFactory, registerPlugin<SwitchViewerPlugin>();)
K_EXPORT_PLUGIN(SwitchViewerFactory(KAboutData("kdevswitchviewer","kdevswitchviewer",ki18n("Switch Viewer"), "0.5", ki18n("Switch between group view"), KAboutData::License_GPL)))

SwitchViewerPlugin::SwitchViewerPlugin(QObject *parent, const QVariantList &args)
:KDevelop::IPlugin(SwitchViewerFactory::componentData(), parent)
{
	Q_UNUSED(args);

	KAction* action = actionCollection()->addAction("previous_view_area");
	action->setText(i18n("Previous Area"));
	action->setShortcut(Qt::ALT + Qt::Key_Left);
	connect(action, SIGNAL(triggered()), SLOT(previousArea()));

	action = actionCollection()->addAction("next_view_area");
	action->setText(i18n("Next Area"));
	action->setShortcut(Qt::ALT + Qt::Key_Right);
	connect(action, SIGNAL(triggered()), SLOT(nextArea()));

	action = actionCollection()->addAction("move_previous_view_area");
	action->setText(i18n("Move View In Previous Area"));
	action->setShortcut(Qt::CTRL + Qt::ALT + Qt::Key_Left);
	connect(action, SIGNAL(triggered()), SLOT(moveViewInPreviousArea()));

	action = actionCollection()->addAction("move_next_view_area");
	action->setText(i18n("Move View In Next Area"));
	action->setShortcut(Qt::CTRL + Qt::ALT + Qt::Key_Right);
	connect(action, SIGNAL(triggered()), SLOT(moveViewInNextArea()));

	action = actionCollection()->addAction("copy_previous_view_area");
	action->setText(i18n("Copy View In Previous Area"));
	action->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::ALT + Qt::Key_Left);
	connect(action, SIGNAL(triggered()), SLOT(copyViewInPreviousArea()));

	action = actionCollection()->addAction("copy_next_view_area");
	action->setText(i18n("Copy View In Next Area"));
	action->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::ALT + Qt::Key_Right);
	connect(action, SIGNAL(triggered()), SLOT(copyViewInNextArea()));

	action = actionCollection()->addAction("clean_view_area");
	action->setText(i18n("Clean View Area"));
	connect(action, SIGNAL(triggered()), SLOT(cleanView()));

	action = actionCollection()->addAction("clean_all_view_area");
	action->setText(i18n("Clean All View Area"));
	connect(action, SIGNAL(triggered()), SLOT(cleanAllView()));

	setXMLFile("kdevswitchviewer.rc");
}

Sublime::MainWindow* SwitchViewerPlugin::activeMainWindow()
{
	Sublime::MainWindow* window = qobject_cast<Sublime::MainWindow*>(KDevelop::ICore::self()->uiController()->activeMainWindow());
	if (!window || !window->area() || !window->area()->activeView())
		return 0;
	return window;
}

void SwitchViewerPlugin::switcher(bool forward, bool move, bool copy)
{
	Sublime::MainWindow* window = SwitchViewerPlugin::activeMainWindow();
	if (!window)
		return;

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

		if (move) {
			KDevelop::IDocument* doc = KDevelop::ICore::self()->documentController()->activeDocument();
			if (doc) {
				SwitchViewerPlugin::activateView(window, areaindex);
				KDevelop::ICore::self()->documentController()->openDocument(doc);
				if (!copy)
					delete area->removeView(activeView);
			}
			/* met le document même s'il exste déjà dans le groupe
			area->addView(activeView->document()->createView(), areaindex);
			delete area->removeView(activeView);*/
		} else {
			SwitchViewerPlugin::activateView(window, areaindex);
		}
	} else if (move && areaindex->viewCount() > 1) {
		area->addView(activeView->document()->createView(), activeView, Qt::Horizontal);
		if (!copy)
			delete area->removeView(activeView);
	}
}

void SwitchViewerPlugin::activateView(Sublime::MainWindow* window, Sublime::AreaIndex* areaindex)
{
	typedef QList<Sublime::View*> QListView;
	QListView views = areaindex->views();
	for (QListView::iterator first = views.begin(), last = views.end(); first != last; ++first)
	{
		if ((*first)->hasWidget() && (*first)->widget()->isVisible()) {
			window->activateView(*first);
			break;
		}
	}
}


void SwitchViewerPlugin::nextArea() const
{
	switcher(true, false);
}

void SwitchViewerPlugin::previousArea() const
{
	switcher(false, false);
}

void SwitchViewerPlugin::moveViewInNextArea() const
{
	switcher(true, true);
}

void SwitchViewerPlugin::moveViewInPreviousArea() const
{
	switcher(false, true);
}

void SwitchViewerPlugin::copyViewInNextArea() const
{
	switcher(true, true, true);
}

void SwitchViewerPlugin::copyViewInPreviousArea() const
{
	switcher(false, true, true);
}

void SwitchViewerPlugin::cleanView(bool all)
{
	Sublime::MainWindow* window = SwitchViewerPlugin::activeMainWindow();
	if (!window)
		return;

	typedef QList<Sublime::View*> QListView;
	Sublime::Area* area = window->area();
	QListView views = area->views();
	QListView remove;

	if (all) {
		for (QListView::iterator it = views.begin(), end = views.end(); it != end; ++it) {
			for (QListView::iterator it2 = it; ++it2 != end;) {
				if ((*it)->document() == (*it2)->document()) {
					remove.push_front(*it);
					break;
				}
			}
		}
	}
	else {
		QListView& viewsSearh = area->indexOf(area->activeView())->views();
		for (QListView::iterator it = viewsSearh.begin(), end = viewsSearh.end(); it != end; ++it) {
			for (QListView::iterator itall = views.begin(), endall = views.end(); itall != endall; ++itall) {
				if (*itall != *it && (*itall)->document() == (*it)->document()) {
					remove.push_front(*it);
				}
			}
		}
	}

	for (QListView::iterator it = remove.begin(), end = remove.end(); it != end; ++it) {
		delete area->removeView(*it);
	}
}


void SwitchViewerPlugin::cleanAllView() const
{
	SwitchViewerPlugin::cleanView(true);
}

void SwitchViewerPlugin::cleanView() const
{
	SwitchViewerPlugin::cleanView(false);
}


#include "switchviewerplugin.moc"
