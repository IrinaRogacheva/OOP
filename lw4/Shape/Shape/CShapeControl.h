#pragma once
#include "IShape.h"
#include <vector>
#include <map>
#include <memory>
#include <functional>

class CShapeControl 
{
public:
	CShapeControl(std::istream& input, std::ostream& output);
	void HandleCommand();

	void FindShapeWithMaxArea() const;
	void FindShapeWithMinPerimeter() const;

	void Draw() const;

private:
	void CreateLineFromInput(std::istream& args);
	void CreateRectangleFromInput(std::istream& args);
	void CreateTriangleFromInput(std::istream& args);
	void CreateCircleFromInput(std::istream& args);

private:
	typedef std::function<void(std::istream& args)> Handler;
	typedef std::map<std::string, Handler> ActionMap;

	std::istream& m_input;
	std::ostream& m_output;

	std::vector<std::shared_ptr<IShape>> m_shapes;
	const ActionMap m_actionMap;
};