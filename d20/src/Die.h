//! @file 
//! @brief Header file for the Die class  
//!
#pragma once
#include <cstdlib>
using namespace std;

class Die {
public:
	Die();
	~Die();
	int roll4()		const;
	int roll6()		const;
	int roll8()		const;
	int roll10()	const;
	int roll12()	const;
	int roll20()	const;
	int roll100()	const;
};
