#pragma once

#include <QDateTime>
#include <QString>

#include "libtelemetry_export.h"

class LIBTELEMETRY_EXPORT Record
{
    private:
        int ID;

        QDateTime TimeStart;
        QDateTime TimeEnd;
        QDateTime TimePenalty;

        QString Notes;


    public:
        Record();

        int       GetID();
        QDateTime GetTimeStart();
        QDateTime GetTimeEnd();
        QDateTime GetTimePenalty();
        QString   GetNotes();


        void SetID(int ID);
        void SetTimeStart(QDateTime timeStart);
        void SetTimeEnd(QDateTime timeEnd);
        void SetTimePenalty(QDateTime timePenalty);
        void SetNotes(QString notes);
};
