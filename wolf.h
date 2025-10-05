#include <cstdlib>
#include <ctime>  
#include <cstdio>

#define MAX_STAMINA 20
#define PLUS_S 5 //сколько зайка сил даст волку
#define EFFORT 1 //затрата сил на перемещение на единицу длинны
#define MAX_SHIFT 2 //максимальное перемещение за один шаг моделирования
#define R_VIEW 4 //радиус обзора 
#define R_DRAP 1 //радиус захвата пищи
#define MAX_COOR 15 //размер карты 
#define CRIT_AGG 0.4 // критическая аггрессивность 
class Wolf {
private:
	int ind = 1; int x; int y; int stamina; double agger; //agger -- ввероятость движения за пищей при ее наличии в радиусе обзора 
public: 
	Wolf(int x, int y, int start_s, double agger); //конструктор волка
	void move_on(int dx, int dy, bool nskip_chase); //передвежение волка
	bool give_s(int ds); // подкормить волка
	int get_x() const;//получить x-координату
	int get_y() const;//получить y-координату
	int get_s() const;//получить текущую вын-ть
	double get_ag() const; //получить агрессивность
	bool is_alive() const; //проверка не умер ли 
	//Rabbit* find_rab(int i); // ищем зайца в зоне видимости(i = 0), в зоне поражения (i = 1)
	//bool chase_rab(Rabbit*); // преследуем зайца
	void update_agg(); //обновить аггресивность
	//bool eat_rab(); //съесть зайца
};

 Wolf::Wolf(int x, int y, int stamina, double start_agger) {
	this->x = x;
	this->y = y;
	this->stamina = stamina;
	this->agger = start_agger;
}
int Wolf::get_x() const {
	return x;
}
int Wolf::get_y() const {
	return y;
}
int Wolf::get_s() const {
	return stamina;
}
double Wolf::get_ag() const  {
	return agger;
}
bool Wolf::give_s(int ds) {
	if (ds + stamina > 1 || ds + stamina < 0) {
		return false;
	}
	else{
		stamina += ds;
		return true;
	}
	
}
void Wolf::update_agg() {
	double new_agg = (double)rand() / RAND_MAX;
	agger = new_agg;
}
bool Wolf::is_alive() const{
	return stamina > 0;
}

#if 0
Rabbit* Wolf::find_rab(int i) { // если i = 0, то в зоне видимости, если i = 1, то ищем зайца в зоне захвата
	int r;
	if (i == 0) r = R_VIEW;
	else if (i == 1) r = R_DRAP;
	else return nullptr;

	for (const auto& rabbit : map.get_rab()) { //get_rab возвращает всех зайцев. Будет брать из контейнера справа зайцев. Const, чтобы зайцев не менять по ссылке
		int dx = abs(rabbit->get_x() - x);
		int dy = abs(rabbit->get_y() - y);
		if (dx > MAX_COOR / 2) dx = MAX_COOR - dx; //если расстояние больше чем половина карты, то измеряем с другой стороны
		if (dy > MAX_COOR / 2) dx = MAX_COOR - dy;
		int distance = dx + dy; // измеряем расстояние по манх-й норме
		if (distance <= r) {
			return rabbit;
		}
		else{
			return nullptr;
		}
	}
}


bool Wolf::chase_rab(Rabbit * rab) {
	if (rab == nullptr) return false;
	int rab_x = rab->get_x();
	int rab_y = rab->get_y();
	
	int dx = x - rab_x;
	int dy = y - rab_y;

	if (dx > MAX_COOR / 2) dx -= -MAX_COOR; //отриц заначение dx движение влево, если короче слева - зайдем слева
	else if (dx < -MAX_COOR / 2) dx += MAX_COOR; // если справа ближе - пойдем справа
	
	if (dy > MAX_COOR / 2) dy -= -MAX_COOR; //отриц заначение dx движение вниз, если короче слева - зайдем снизу
	else if (dy < -MAX_COOR / 2) dy += MAX_COOR; // если сверху ближе - пойдем сверху

	move_on(dx, dy, true); //двигаемя пропуская фазу преследования
	return true;
}

bool Wolf::eat_rab() {
	Rabbit* target = find_rab(1);
	if (target != nullptr) {
		map.kill_rab(target);
		s += PLUS_S;
		return true;
	}
	else return false;
}




#endif

void Wolf::move_on(int dx, int dy, bool nskip_chase  = false) { //dx, dy предлагаемые параметры перемещения
	if (dx > MAX_SHIFT) dx = MAX_SHIFT; //не можем переместиться дальше, чем можем
	if (dy > MAX_SHIFT) dy = MAX_SHIFT;
	if (dx < -MAX_SHIFT) dx = -MAX_SHIFT;
	if (dy < -MAX_SHIFT) dy = -MAX_SHIFT;
	
#if 0
	if (nskip_chase && find_rab(0) != nullptr && get_ag() >= CRIT_AGG) { //если заяц по близости есть, будем его преследовать
		return chaise_rab(find_rab(0));
	}
#endif
	// Рассчитываем новые координаты
	int new_x = x + dx;
	int new_y = y + dy;

	// Обрабатываем выход за границы (тор)
	if (new_x < 0) new_x = MAX_COOR + new_x;
	else if (new_x > MAX_COOR) new_x = new_x - MAX_COOR - 1; // не пропускаем нулевую клетку

	if (new_y < 0) new_y = MAX_COOR + new_y;
	else if (new_y > MAX_COOR) new_y = new_y - MAX_COOR - 1; // не пропускаем нулевую клетку

	// Применяем новые координаты
	stamina -= (abs(x - new_x) + abs(y - new_y)) * EFFORT;
	if (stamina <= 0) {
		//map.kill_wolf(this);
		return;
	}
	x = new_x;
	y = new_y;
	update_agg();
} 

