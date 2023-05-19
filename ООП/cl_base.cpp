#include "cl_base.h"
#include <queue>
cl_base::cl_base(cl_base* p_head_object, string s_name, int id) {
	//конструктор
	this->p_head_object = p_head_object;
	this->s_name = s_name;
	this->state = 0;
	this->class_id = id;
	if (p_head_object != nullptr) {
		//добавление в вектор указатель на текущий объект
			p_head_object->p_sub_objects.push_back(this);
		// добавления указателя текущего (нового созданного) объекта в состав указателей на подчиненные объекты
	}
}
cl_base::~cl_base() {
	//деструктор
	for (int i = 0; i < p_sub_objects.size(); i++) {
		//проходим по вектору, чтобы вызвать деструкторы для каждого элемента
			delete p_sub_objects[i];
	}
}
string cl_base::get_name() {
	//метод для получения имени
	return s_name;
}
cl_base* cl_base::get_head() {
	//метод получения указателя на головной объект текущего объекта
		return p_head_object;
}
cl_base* cl_base::get_sub_object(string s_name) {
	//Метод получения указателя на непосредственно подчиненный объект по его имени
	for (int i = 0; i < p_sub_objects.size(); i++) {
		//Если объект не найден, то возвращает nullptr.
			if (p_sub_objects[i]->get_name() == s_name) {
				return p_sub_objects[i];
			}
	}
	return nullptr;
}
void cl_base::print_tree() {
	//метод вывода наименований объектов в дереве иерархии слева направо и сверху вниз
		if (!p_sub_objects.empty()) {
			//если вектор не пустой
			cout << endl << get_name();
			for (int i = 0; i < p_sub_objects.size(); i++) {
				cout << " " << p_sub_objects[i]->get_name();
				p_sub_objects[i]->print_tree();
				//вызов рекурсивного метода print_tree
			}
		}
}
bool cl_base::set_name(string s_new_name) {
	//Метод редактирования имени объекта
		if (get_head() != nullptr) {
			//Один параметр строкового типа сожержит новое имя объекта
				for (int i = 0; i < get_head()->p_sub_objects.size(); i++) {
					//Если нет дубляжа имени подчиненных объектов у головного, то редактирует имя и возвращает значение "Истина", иначе - "Ложь"
						if (get_head()->p_sub_objects[i]->get_name() == s_new_name) {
							return false;
						}
				}
		}
	this->s_name = s_new_name;
	return true;
}
//-------------------------КВ2
int cl_base::count(string s_name) {
	//вспомогательный метод подсчитывающий кол-во вхождений объектов с данным именем от текущего узла
		int counter = 0;
	if (this->get_name() == s_name) {
		//проверка текущего элемента
		counter++;
	}
	for (auto p_sub_object : p_sub_objects) {
		//цикл по подчиненным объектам
		counter += p_sub_object->count(s_name);
	}
	return counter;
}
cl_base* cl_base::search_object(string s_name) {
	//метод поиска объекта на ветке дереве иерархии от текущего по имени
	if (this->count(s_name) != 1) {
		return nullptr;
	}
	if (this->get_name() == s_name) {
		return this;
	}
	cl_base* pruf = nullptr;
	for (int i = 0; i < p_sub_objects.size(); i++) {
		pruf = p_sub_objects[i]->search_object(s_name);
		if (pruf != nullptr) {
			break;
		}
	}
	return pruf;
}
cl_base* cl_base::find_object_from_current(string s_name) { // метод поиска объекта на дереве иерархии по имени от текущего объекта
		return search_object(s_name);
}
cl_base* cl_base::find_object_from_root(string s_name) { //метод поиска объекта на дереве иерархии по имени
		cl_base* temp = this;
	while (temp->get_head() != nullptr) {
		temp = temp->get_head();
	}
	return temp->find_object_from_current(s_name);
}
void cl_base::r_point(int r_num) {
	//метод установки готовности объекта, в качестве параметра передается переменная целого типа, содержит номер состояния
		bool all_parents_ready = true;
	if (this->get_head() != nullptr) {
		cl_base* current_obj = this->get_head();
		while (current_obj != nullptr) {
			if (current_obj->state == 0) {
				all_parents_ready = false;
				break;
			}
			current_obj = current_obj->get_head();
		}
	}
	if (all_parents_ready || r_num == 0) {
		this->state = r_num;
		if (r_num == 0) {
			for (auto p_sub_object : p_sub_objects) {
				p_sub_object->r_point(0);
			}
		}
	}
}
void cl_base::print_tree_from_current(string tab) {
	//метод вывода иерархии объектов (дерева или ветки) от текущего объекта;
	cout << endl << tab << this->s_name;
	for (auto p_sub_object : p_sub_objects) {
		p_sub_object->print_tree_from_current(tab + " ");
	}
}
void cl_base::print_rpoint_and_tree_from_root(string tab) { //метод вывода иерархии объектов(дерева или ветки) и отметок их готовности от текущего объекта;
	string s;
	if (this->state != 0) {
		s = " is ready";
	}
	else {
		s = " is not ready";
	}
	cout << tab << this->s_name << s;
	for (auto p_sub_object : p_sub_objects) {
		cout << endl;
		p_sub_object->print_rpoint_and_tree_from_root(tab + " ");
	}
}
//-------------------------------------КВ3
cl_base* cl_base::find_child(string s_name) {
	//поиск дочернего объекта с определенным именем внутри родительского объекта
	for (int i = 0; i < p_sub_objects.size(); i++) {
		//перебор всех значений в векторе p_sub_objects
		if (p_sub_objects[i]->s_name == s_name) {
			//если значение поля s_name текущего объекта равно переданной строке
			return p_sub_objects[i];
		}
	}
	return nullptr;
}
cl_base* cl_base::get_root() {
	//метод получения указателя на корневой объект
	cl_base* p_root = this;
	while (p_root->get_head() != nullptr) {
		//аока у текущего объекта есть родитель
		p_root = p_root->get_head();
	}
	return p_root;
}
cl_base* cl_base::find_obj_by_coord(string s_coord) {
	//получение указателя на любой объект в составе дерева иерархии объектов согласно пути(координаты)
		if (s_coord == "/") {
			return get_root();
		}
	if (s_coord == ".") {
		return this;
	}
	if (s_coord[0] == '.') {
		//если передана строка, начинающаяся с '.'
		return this->search_object(s_coord.substr(1));
	}
	if (s_coord.find("//") == 0) {
		//если в начале строки находит "//"
		return get_root()->search_object(s_coord.substr(2));
	}
	if (s_coord[0] == '/') {
		//если передана строка, начинающаяся с '/'
		return get_root()->find_obj_by_coord(s_coord.substr(1));
	}
	int buf = s_coord.size();
	for (int i = 0; i < s_coord.size(); i++) {
		//цикл проходит по пути и ищет '/', чтобы запомнить позицию '/'
		if (s_coord[i] == '/') {
			buf = i;
			break;
		}
	}
	//Создание подстроки из строки s_coord с помощью метода substr.
		//Подстрока будет содержать все символы из s_coord до индекса buf
		string str = s_coord.substr(0, buf);
	for (int i = 0; i < this->p_sub_objects.size(); i++) {
		if (p_sub_objects[i]->get_name() == str) {
			//если найден объект с нужным именем
			if (buf == s_coord.size()) {
				return p_sub_objects[i];
			}
			return p_sub_objects[i]->find_obj_by_coord(s_coord.substr(buf + 1));
		}
	}
	return nullptr;
}
bool cl_base::set_head(cl_base* obj) {
	//переопределение головного объекта для текущего в дереве иерархии
	if (obj->find_child(this->get_name())) {
		//если объект obj уже является родительским для текущего объекта
		return true;
	}
	obj->p_sub_objects.push_back(this);
	//перебор всех объектов в списке p_sub_objects родительского объекта текущего объекта
		for (auto it = this->get_head()->p_sub_objects.begin(); it != this -> get_head()->p_sub_objects.end(); it++) {
			if (*it == this) {
				//если текущий элемент списка равен текущему объекту
				this->get_head()->p_sub_objects.erase(it);
				break;
			}
		}
	return false;
}
void cl_base::delete_obj(string s_name) {
	//удаление подчиненного объекта по наименованию
	cl_base* del = this->find_object_from_root(s_name);
	//поиск объекта с заданным именем, начиная с корневого объекта
	if (del == nullptr) {
		//если объект не найден
		return;
	}
	//перебор всех дочерних объектов текущего объекта
	for (this->p_head_object->child_iterator = p_sub_objects.begin(); this -> p_head_object->child_iterator != p_sub_objects.end(); this->p_head_object -> child_iterator++) {
		if (*this->p_head_object->child_iterator == del) {
			//если текущий дочерний объект равен объекту, который нужно удалить
			p_sub_objects.erase(this->p_head_object->child_iterator);
			return;
		}
	}
}
bool cl_base::search_obj_in_branch_point(cl_base* obj) {
	//определение, является ли заданный объект родителем текущего объекта
	while (obj->get_head() != nullptr) {
		//пока obj не дойдёт до корневого объекта
		if (obj == this) {
			//если текущий объект равен obj, значит он является родителем текущего объекта
				return true;
		}
		obj = obj->get_head();
		//переход к родительскому объекту
	}
	return false;
}
cl_base* cl_base::find_obj_by_name_in_branch(cl_base* obj) {
	// поиск дочернего объекта с определенным именем в иерархии объектов, которые происходят от данного объекта
	queue<cl_base*> qu;
	//очередь для хранения объектов, которые нужно проверить
	cl_base* buf = nullptr;
	//указатель на объект, который надо проверить
	qu.push(this);
	//добавление текущего объекта в очередь
	while (!qu.empty()) {
		if (qu.front()->get_name() == s_name) {
			//если имя текущего объекта равно искомому имени
			if (buf == nullptr) {
				buf = qu.front();
				//присвоение текущего объекта
			}
			else {
				return buf;
			}
		}
		for (auto p_sub_object : qu.front()->p_sub_objects) {
			//цикл добавления всех дочерних объектов текущего объекта в очередь
			qu.push(p_sub_object);
		}
		qu.pop();
	}
	return nullptr;
}
//-----------------------------------------------------КВ4
void cl_base::set_connect(TYPE_SIGNAL signal, cl_base* p_object, TYPE_HANDLER
	p_ob_hendler) { //установка связи между сигналом текущего объекта и обработчиком целевого объекта
		str_connect* p_value;
	for (int i = 0; i < connects.size(); i++) {
		if (connects[i]->p_signal == signal && connects[i]->p_cl_base ==
			p_object && connects[i]->p_hendler == p_ob_hendler) {
			return;
		}
	}
	p_value = new str_connect();
	p_value->p_signal = signal;
	p_value->p_cl_base = p_object;
	p_value->p_hendler = p_ob_hendler;
	connects.push_back(p_value);
}
void cl_base::emit_signal(TYPE_SIGNAL signal, string& s_command) {
	//выдача сигнала от текущего объекта с передачей строковой переменной. Включенный объект может выдать или обработать сигнал
		if (!this->state) {
			return;
		}
	TYPE_HANDLER handler;
	//указатель handler типа TYPE_HANDLER
	cl_base* p_object;
	(this->*signal)(s_command);
	for (int i = 0; i < connects.size(); i++) {
		if (connects[i]->p_signal == signal) {
			handler = connects[i]->p_hendler;
			p_object = connects[i]->p_cl_base;
			if (connects[i]->p_cl_base->state) {
				(p_object->*handler)(s_command);
			}
		}
	}
}
void cl_base::delete_connect(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER
	p_ob_hendler) { //удаление (разрыва) связи между сигналом текущего объекта и обработчиком целевого объекта
		for (int i = 0; i < connects.size(); i++) {
			if (connects[i]->p_signal == p_signal && connects[i]->p_cl_base ==
				p_object && connects[i]->p_hendler == p_ob_hendler) {
				connects.erase(connects.begin() + i);
				return;
			}
		}
}
string cl_base::get_absolute_path() { //получение абослютного пути объекта
	string path; //путь
	cl_base* p_obj = this;
	while (p_obj->p_head_object != nullptr) {
		path = "/" + p_obj->get_name() + path;
		p_obj = p_obj->p_head_object;
	}
	if (path == "") {
		path = "/";
	}
	return path;
}
void cl_base::turn_on_tree() { //включение готовности всего дерева
		state = 1;
	for (int i = 0; i < p_sub_objects.size(); i++) {
		p_sub_objects[i]->turn_on_tree();
	}
}
int cl_base::get_class_id() { //получение номера (id) класса объекта
	return class_id;
}
