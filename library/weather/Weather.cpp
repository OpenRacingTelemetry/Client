#include "Weather.h"

Weather::Weather()
{

}

Weather::Weather(QString comments)
{
    this->comments=comments;
}

QString Weather::GetComments()
{
    return this->comments;
}
