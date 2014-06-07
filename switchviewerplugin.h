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

#ifndef SWITCHAREAPLUGIN_H
#define SWITCHAREAPLUGIN_H

#include <kdevplatform/interfaces/iplugin.h>
#include <QtCore/QVariant>

namespace Sublime{
	class MainWindow;
	class AreaIndex;
	class MainWindow;
};

class SwitchViewerPlugin: public KDevelop::IPlugin {
	Q_OBJECT
public:
	explicit SwitchViewerPlugin(QObject *parent, const QVariantList &args = QVariantList());
	virtual ~SwitchViewerPlugin() {};

public slots:
	void nextArea() const;
	void previousArea() const;

	void moveViewInNextArea() const;
	void moveViewInPreviousArea() const;

	void copyViewInNextArea() const;
	void copyViewInPreviousArea() const;

	void cleanView() const;
	void cleanAllView() const;

public:
	//inline void areaSwitcher(bool forward = true) const;
	//inline void moveAreaSwitcher(bool forward = true) const;

private:
	inline static Sublime::MainWindow* activeMainWindow();
	static void switcher(bool forward, bool move, bool copy = false);
	static void activateView(Sublime::MainWindow*, Sublime::AreaIndex*);
	static void cleanView(bool all);

private:
};

#endif
