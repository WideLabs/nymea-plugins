/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* Copyright 2013 - 2020, nymea GmbH
* Contact: contact@nymea.io
*
* This file is part of nymea.
* This project including source code and documentation is protected by
* copyright law, and remains the property of nymea GmbH. All rights, including
* reproduction, publication, editing and translation, are reserved. The use of
* this project is subject to the terms of a license agreement to be concluded
* with nymea GmbH in accordance with the terms of use of nymea GmbH, available
* under https://nymea.io/license
*
* GNU Lesser General Public License Usage
* Alternatively, this project may be redistributed and/or modified under the
* terms of the GNU Lesser General Public License as published by the Free
* Software Foundation; version 3. This project is distributed in the hope that
* it will be useful, but WITHOUT ANY WARRANTY; without even the implied
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this project. If not, see <https://www.gnu.org/licenses/>.
*
* For any further details and any questions please contact us under
* contact@nymea.io or see our FAQ/Licensing Information on
* https://nymea.io/license/faq
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef INTEGRATIONPLUGINSHELLY_H
#define INTEGRATIONPLUGINSHELLY_H

#include "integrations/integrationplugin.h"

#include "extern-plugininfo.h"

#include <QHostAddress>

class ZeroConfServiceBrowser;
class PluginTimer;

class MqttChannel;

class IntegrationPluginShelly: public IntegrationPlugin
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "io.nymea.IntegrationPlugin" FILE "integrationpluginshelly.json")
    Q_INTERFACES(IntegrationPlugin)


public:
    explicit IntegrationPluginShelly();
    ~IntegrationPluginShelly() override;

    void init() override;
    void discoverThings(ThingDiscoveryInfo *info) override;
    void setupThing(ThingSetupInfo *info) override;
    void postSetupThing(Thing *thing) override;
    void thingRemoved(Thing *thing) override;
    void executeAction(ThingActionInfo *info) override;

private slots:
    void onClientConnected(MqttChannel* channel);
    void onClientDisconnected(MqttChannel* channel);
    void onPublishReceived(MqttChannel* channel, const QString &topic, const QByteArray &payload);

    void updateStatus();
    void reconfigureUnconnected();

private:
    void setupShellyGateway(ThingSetupInfo *info);
    void setupShellyChild(ThingSetupInfo *info);

    QHostAddress getIP(Thing *thing) const;

private:
    ZeroConfServiceBrowser *m_zeroconfBrowser = nullptr;
    PluginTimer *m_statusUpdateTimer = nullptr;
    PluginTimer *m_reconfigureTimer = nullptr;

    QHash<Thing*, MqttChannel*> m_mqttChannels;
};

#endif // INTEGRATIONPLUGINSHELLY_H
