#include "AModel.h"

using namespace Core;

AModel::AModel()
{

}


std::map<std::string, AModel*>* AModelFactory::models = new std::map<std::string, AModel*>();

AModel* AModelFactory::createModel(std::string path)
{
	auto it = models->find(path);
	if (it != models->end())
	{
		return it->second;
	}

	AModel* model = new AModel(path);
	models->insert(std::pair<std::string, AModel*>(path, model));
	return model;
}
