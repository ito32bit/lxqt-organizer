/***************************************************************************
 *   Author aka. crispina                 *
 *   crispinalan@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#include "daylistmodel.h"

DayListModel::DayListModel(QObject *parent)
{
    Q_UNUSED(parent)
    this->modelAppointmentList= QList<Appointment>();

}

DayListModel::DayListModel(const QList<Appointment> &appointmentList, QObject *parent)
{
    Q_UNUSED(parent)
    this->modelAppointmentList=appointmentList;

}

void DayListModel::addAppointment(Appointment &appointment)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    this->modelAppointmentList.append(appointment);
    endInsertRows();
}

void DayListModel::updateAppointment(Appointment &appointment, int index)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    Appointment a = modelAppointmentList.value(index);
    a.m_title= appointment.m_title;
    a.m_location=appointment.m_location;
    a.m_description=appointment.m_description;
    a.m_startTime=appointment.m_startTime;
    a.m_endTime=appointment.m_endTime;
    a.m_category=appointment.m_category;
    a.m_isFullDay=appointment.m_isFullDay;
    modelAppointmentList.removeAt(index);
    modelAppointmentList.insert(index,a);
    endInsertRows();
}

Appointment DayListModel::getAppointment(int index)
{
    Appointment a = modelAppointmentList.value(index);
    return a;
}

void DayListModel::clearAllAppointment()
{
    beginResetModel();
    modelAppointmentList.clear();
    endResetModel();
}

void DayListModel::removeAppointment(int idx)
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    modelAppointmentList.removeAt(idx);
    endRemoveRows();
}

void DayListModel::setNewLineSpacing(int spacing)
{
    flagSpacing=spacing;
}





int DayListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return modelAppointmentList.size();
}

QVariant DayListModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();
    if (index.row() >= modelAppointmentList.size() || index.row() < 0)
        return QVariant();
    const Appointment& appointment = modelAppointmentList.at(index.row());
    if (role == Qt::DisplayRole) {


        QString details=QStringLiteral("default");
        //More to do..
        QTime starts =QTime::fromString(appointment.m_startTime);
        QTime ends =QTime::fromString(appointment.m_endTime);

        if (appointment.m_isFullDay==1)
        {


            if(flagSpacing==0)
            {
                details=QStringLiteral("All Day Event: ")+appointment.m_title
                        + QStringLiteral(" (")+appointment.m_location+QStringLiteral(") ")
                        +appointment.m_description;

            }
            else if(flagSpacing==1)
            {
                details=QStringLiteral("All Day Event: ")+appointment.m_title
                        + QStringLiteral(" (")+appointment.m_location+QStringLiteral(") ")
                        +appointment.m_description+QLatin1Char('\n');
            }
            else {
                details=QStringLiteral("All Day Event: ")+appointment.m_title
                        + QStringLiteral(" (")+appointment.m_location+QStringLiteral(") ")
                        +appointment.m_description;
            }

        }
        else {

            if(flagSpacing==0)
            {
                details =starts.toString(QStringLiteral("hh:mm"))+QStringLiteral(" to ")+ends.toString(QStringLiteral("hh:mm"))
                        + QLatin1Char(' ')+appointment.m_title+QStringLiteral(" (")+appointment.m_location+ QStringLiteral(") ")
                        + appointment.m_description;

            }
            else if(flagSpacing==1)
            {
                details =starts.toString(QStringLiteral("hh:mm"))+QStringLiteral(" to ")+ends.toString(QStringLiteral("hh:mm"))
                        + QLatin1Char(' ')+appointment.m_title+QStringLiteral(" (")+appointment.m_location+ QStringLiteral(") ")
                        + appointment.m_description+QLatin1Char('\n');
            }
            else {
                details =starts.toString(QStringLiteral("hh:mm"))+QStringLiteral(" to ")+ends.toString(QStringLiteral("hh:mm"))
                        + QLatin1Char(' ')+appointment.m_title+QStringLiteral(" (")+appointment.m_location+ QStringLiteral(") ")
                        + appointment.m_description;
            }
        }

        return details;
    }



    return QVariant();
}
