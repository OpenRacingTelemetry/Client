#include "Record.h"

Record::Record()
{
    this->TimeStart=QDateTime::fromString("00:00:00,000","HH:mm:ss,zzz");
    this->TimeEnd=QDateTime::fromString("00:00:00,000","HH:mm:ss,zzz");
    this->TimePenalty=QDateTime::fromString("00:00:00,000","HH:mm:ss,zzz");
}

int Record::GetID()
{
    return this->ID;
}

QDateTime Record::GetTimeStart()
{
    return this->TimeStart;
}

QDateTime Record::GetTimeEnd()
{
    return this->TimeEnd;
}

QDateTime Record::GetTimePenalty()
{
    return this->TimePenalty;
}

QString Record::GetNotes()
{
    return this->Notes;
}

void Record::SetID(int ID)
{
    this->ID=ID;
}

void Record::SetTimeStart(QDateTime timeStart)
{
    this->TimeStart=timeStart;
}

void Record::SetTimeEnd(QDateTime timeEnd)
{
    this->TimeEnd=timeEnd;
}

void Record::SetTimePenalty(QDateTime timePenalty)
{
    this->TimePenalty=timePenalty;
}

void Record::SetNotes(QString notes)
{
    this->Notes=notes;
}
