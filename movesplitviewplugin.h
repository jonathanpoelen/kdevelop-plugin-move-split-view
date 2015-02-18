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

#ifndef MOVESPLITVIEWPLUGIN_H
#define MOVESPLITVIEWPLUGIN_H

#include <kdevplatform/interfaces/iplugin.h>
#include <QtCore/QVariant>

namespace Sublime{
	class MainWindow;
	class AreaIndex;
	class MainWindow;
};

class MoveSplitViewPluginImpl;

class MoveSplitViewPlugin: public KDevelop::IPlugin {
	Q_OBJECT
	friend MoveSplitViewPluginImpl;

public:
	explicit MoveSplitViewPlugin(QObject *parent, const QVariantList &args = QVariantList());
	virtual ~MoveSplitViewPlugin() {};

public slots:
	void moveViewInNextArea() const;
	void moveViewInPreviousArea() const;

	void copyViewInNextArea() const;
	void copyViewInPreviousArea() const;

	void cleanView() const;
	void cleanAllView() const;
};

#endif
