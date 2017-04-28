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

#ifndef KDEV_MOVE_SPLIT_VIEW_PLUGIN_H
#define KDEV_MOVE_SPLIT_VIEW_PLUGIN_H

#include <kdevplatform/interfaces/iplugin.h>
#include <QtCore/QVariant>

class KDevMoveSplitViewPlugin: public KDevelop::IPlugin {
	Q_OBJECT
public:
	explicit KDevMoveSplitViewPlugin(QObject *parent, const QVariantList &args = QVariantList());
	virtual ~KDevMoveSplitViewPlugin();
};

#endif
