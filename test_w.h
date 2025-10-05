#include "wolf.h"
#include <cassert>

bool t_create(Wolf* wolf) { //тест на корректрное создание волка
	int x = wolf->get_x();
	int y = wolf->get_y();
	int s = wolf->get_s();
	int agg = wolf->get_ag();
	assert(x < 0 || x > MAX_COOR || y < 0 || y > MAX_COOR || s > MAX_STAMINA || s < 0 || agg < 0 || agg > 1);
	//printf("Wolf created correctly");
	return true;
}
bool t_update_agg(Wolf* wolf) {
	if (wolf->get_ag() > 1 || wolf->get_ag() < 0) {
		printf("Can't update agger");
		return false;
	}
	else return true;
}
bool t_give_stamina(Wolf* wolf) {
	assert(wolf->get_s() < 0 || wolf->get_s() > 1);
	return true;
}
bool t_move_on(Wolf* wolf) {
	int x = wolf->get_x();
	int y = wolf->get_y();
	int s = wolf->get_s();
	int agg = wolf->get_ag();
	assert(x < 0 || x > MAX_COOR || y < 0 || y > MAX_COOR || s > MAX_STAMINA || s < 0 || agg < 0 || agg > 1); 
	return true;
}







