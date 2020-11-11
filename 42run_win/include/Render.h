#pragma once
#include "Model.h"
#include <vector>
class Render
{
public:
	void AddModel(Model *mod);
	void DrawModels();

public:
private:
	std::vector<Model*> models;
};
