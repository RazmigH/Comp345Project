//! @file 
//! @brief Implementation file for the Die class  
//!
#include "Die.h"

Die::Die()
{
}
Die::~Die()
{
}
int Die::roll4() const
{
	return (rand() % 4) + 1;
}

int Die::roll6() const
{
	return (rand() % 6) + 1;
}

int Die::roll8() const
{
	return (rand() % 8) + 1;
}

int Die::roll10() const
{
	return (rand() % 10) + 1;;
}

int Die::roll12() const
{
	return (rand() % 12) + 1;;
}

int Die::roll20() const
{
	return (rand() % 20) + 1;;
}

int Die::roll100() const
{
	return (rand() % 100) + 1;;
}