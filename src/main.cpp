#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>

class $modify(MyEditorUI, EditorUI) {
	void doCopyObjects(bool p0) {
		auto selected = EditorUI::getSelectedObjects();
		if (selected && selected->count()) {
			std::string result_str = "";
			for (int i = 0; i < selected->count(); i++) {
				auto obj = static_cast<GameObject*>(selected->objectAtIndex(i));
				auto str_repr = obj->getSaveString(nullptr);
				result_str += str_repr + std::string(";");
			}
			clipboard::write(result_str);
		}
		EditorUI::doCopyObjects(p0);
	}

	void doPasteObjects(bool p0) {
		auto str = clipboard::read();
		auto editor_layer = LevelEditorLayer::get();
		auto obj_array = editor_layer->createObjectsFromString(str, true, true);
		if (obj_array && obj_array->count()) {
			editor_layer->m_undoObjects->addObject(
				UndoObject::createWithArray(obj_array, UndoCommand::Paste)
			);
			EditorUI::deselectAll();
			EditorUI::selectObjects(obj_array, true);
			editor_layer->keyBackClicked();
		} 
	}

};