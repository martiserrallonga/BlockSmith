#pragma once

#include <functional>
#include <string>
#include <vector>


class DropdownValue
{
public:
	using Callback = std::function<void(int)>;

	DropdownValue() = default;
	DropdownValue(std::string label, std::vector<std::string> enumKeys, int defaultValue = 0, Callback callback = nullptr);

	void renderInMenu();

private:
	std::string _label;
	std::vector<std::string> _enumKeys;
	int _currentValue = 0;

	Callback _onValueChanges;
};
