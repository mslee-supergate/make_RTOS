#ifndef LIB_ARMV7A_SWITCH_H_
#define LIB_ARMV7A_SWITCH_H_

/* 첫 번째 태스크의 문맥을 복원하고 실행을 시작한다. */
void Arch_start(void);

/* 현재 태스크 문맥을 저장하고 다음 태스크로 전환한다. */
void Arch_context_switching(void);

#endif /* LIB_ARMV7A_SWITCH_H_ */