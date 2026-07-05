#ifndef INC_RUNTIME_ERROR_STUB_H_
#define INC_RUNTIME_ERROR_STUB_H_

void RuntimeErrorStub_Reset(void);
const char * RuntimeErrorStub_GetLastError(void);
int RuntimeErrorStub_GetLastParameter(void);

#endif /* INC_RUNTIME_ERROR_STUB_H_ */