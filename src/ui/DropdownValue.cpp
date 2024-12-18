#include "DropdownValue.h"
#include <imgui.h>


DropdownValue::DropdownValue(std::string label, std::vector<std::string> enumKeys, const int defaultValue, Callback callback)
	:_label(std::move(label))
	, _enumKeys(std::move(enumKeys))
	, _currentValue(defaultValue)
	, _onValueChanges(std::move(callback)) {}

void DropdownValue::renderImGui() {
	if (!ImGui::BeginCombo("Log Level", _enumKeys.at(_currentValue).c_str())) return;

	int nextValue = _currentValue;
	for (int i = 0; i < ssize(_enumKeys); ++i) {
		const bool isSelected = i == _currentValue;
		if (ImGui::Selectable(_enumKeys.at(i).c_str(), isSelected)) nextValue = i;
		if (isSelected) ImGui::SetItemDefaultFocus();
	}

	if (nextValue != _currentValue) {
		_currentValue = nextValue;
		_onValueChanges(_currentValue);
	}

	ImGui::EndCombo();
}
