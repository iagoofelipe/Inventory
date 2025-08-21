#pragma once

#include "consts.h"
#include <vector>

class AppModel
{
public:
	AppModel();
	~AppModel();

	void DeleteLater(Movement* p);
	void Release();

private:
	bool cleaned;
	std::vector<Movement*> toDelete_Movement;
};

extern AppModel* pAppModel;