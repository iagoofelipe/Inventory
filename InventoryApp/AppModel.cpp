#include "AppModel.h"

#include <wx/wx.h>

AppModel* pAppModel = new AppModel();

AppModel::AppModel()
	: cleaned(false)
{
}

AppModel::~AppModel()
{
	Release();
}

void AppModel::DeleteLater(Movement* p)
{
	toDelete_Movement.push_back(p);
}

void AppModel::Release()
{
	if (cleaned)
		return;

	cleaned = true;
	for (Movement* ptr : toDelete_Movement)
		delete ptr;

	toDelete_Movement.clear();
}