#ifndef INC_LIGHT_CONTROLLER_H_
#define INC_LIGHT_CONTROLLER_H_

void LightController_Create(void);
void LightController_Destroy(void);
//BOOL LightController_Add(int id, LightDriver);
void LightController_On(int id);
void LightController_Off(int id);

#endif /* INC_LIGHT_CONTROLLER_H_ */