#include <cstdlib>
#include <ctime>  
#include <cstdio>

#define MAX_STAMINA 20
#define PLUS_S 5 //������� ����� ��� ���� �����
#define EFFORT 1 //������� ��� �� ����������� �� ������� ������
#define MAX_SHIFT 2 //������������ ����������� �� ���� ��� �������������
#define R_VIEW 4 //������ ������ 
#define R_DRAP 1 //������ ������� ����
#define MAX_COOR 15 //������ ����� 
#define CRIT_AGG 0.4 // ����������� �������������� 
class Wolf {
private:
	int ind = 1; int x; int y; int stamina; double agger; //agger -- ����������� �������� �� ����� ��� �� ������� � ������� ������ 
public: 
	Wolf(int x, int y, int start_s, double agger); //����������� �����
	void move_on(int dx, int dy, bool nskip_chase); //������������ �����
	bool give_s(int ds); // ���������� �����
	int get_x() const;//�������� x-����������
	int get_y() const;//�������� y-����������
	int get_s() const;//�������� ������� ���-��
	double get_ag() const; //�������� �������������
	bool is_alive() const; //�������� �� ���� �� 
	//Rabbit* find_rab(int i); // ���� ����� � ���� ���������(i = 0), � ���� ��������� (i = 1)
	//bool chase_rab(Rabbit*); // ���������� �����
	void update_agg(); //�������� �������������
	//bool eat_rab(); //������ �����
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
Rabbit* Wolf::find_rab(int i) { // ���� i = 0, �� � ���� ���������, ���� i = 1, �� ���� ����� � ���� �������
	int r;
	if (i == 0) r = R_VIEW;
	else if (i == 1) r = R_DRAP;
	else return nullptr;

	for (const auto& rabbit : map.get_rab()) { //get_rab ���������� ���� ������. ����� ����� �� ���������� ������ ������. Const, ����� ������ �� ������ �� ������
		int dx = abs(rabbit->get_x() - x);
		int dy = abs(rabbit->get_y() - y);
		if (dx > MAX_COOR / 2) dx = MAX_COOR - dx; //���� ���������� ������ ��� �������� �����, �� �������� � ������ �������
		if (dy > MAX_COOR / 2) dx = MAX_COOR - dy;
		int distance = dx + dy; // �������� ���������� �� ����-� �����
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

	if (dx > MAX_COOR / 2) dx -= -MAX_COOR; //����� ��������� dx �������� �����, ���� ������ ����� - ������ �����
	else if (dx < -MAX_COOR / 2) dx += MAX_COOR; // ���� ������ ����� - ������ ������
	
	if (dy > MAX_COOR / 2) dy -= -MAX_COOR; //����� ��������� dx �������� ����, ���� ������ ����� - ������ �����
	else if (dy < -MAX_COOR / 2) dy += MAX_COOR; // ���� ������ ����� - ������ ������

	move_on(dx, dy, true); //�������� ��������� ���� �������������
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

void Wolf::move_on(int dx, int dy, bool nskip_chase  = false) { //dx, dy ������������ ��������� �����������
	if (dx > MAX_SHIFT) dx = MAX_SHIFT; //�� ����� ������������� ������, ��� �����
	if (dy > MAX_SHIFT) dy = MAX_SHIFT;
	if (dx < -MAX_SHIFT) dx = -MAX_SHIFT;
	if (dy < -MAX_SHIFT) dy = -MAX_SHIFT;
	
#if 0
	if (nskip_chase && find_rab(0) != nullptr && get_ag() >= CRIT_AGG) { //���� ���� �� �������� ����, ����� ��� ������������
		return chaise_rab(find_rab(0));
	}
#endif
	// ������������ ����� ����������
	int new_x = x + dx;
	int new_y = y + dy;

	// ������������ ����� �� ������� (���)
	if (new_x < 0) new_x = MAX_COOR + new_x;
	else if (new_x > MAX_COOR) new_x = new_x - MAX_COOR - 1; // �� ���������� ������� ������

	if (new_y < 0) new_y = MAX_COOR + new_y;
	else if (new_y > MAX_COOR) new_y = new_y - MAX_COOR - 1; // �� ���������� ������� ������

	// ��������� ����� ����������
	stamina -= (abs(x - new_x) + abs(y - new_y)) * EFFORT;
	if (stamina <= 0) {
		//map.kill_wolf(this);
		return;
	}
	x = new_x;
	y = new_y;
	update_agg();
} 

