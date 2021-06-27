#pragma once
#include "Character.h"
#include <string>

// 미사일 오브젝트 관리
struct BOSS_MISSILE
{
	Image _image; // 미사일 개별 이미지정보
	INT nLife; // 미사일 개별 생명
	DIRECT nDirect; // 미사일 개별 방향
	DWORD OldTime; // 미사일 개별 이전이동시각 

};
// 전체 미사일 관리
struct BOSS_MISSILE_INFO
{
	DWORD MoveTime; // 미사일 전체 이동 시간 간격
	DWORD FireTime; // 미사일 전체 발사 시간 간격
	DWORD OldFireTime; // 미사일 전체 이전 발사 시각
	BOSS_MISSILE sMissile[30]; // 최대 출력 미사일 개수
};

class Boss : public Character
{
public:
	INT Index;
	Pat_Info PatInfo; // 패턴 정보

	DIRECT Direcct;					// 보스 이동 방향
	DWORD AppearTime;				// 출현시각
	DWORD MissileFireTime;			// 미사일 발사 시간 간격
	DWORD MissileOldTime;			// 이전 미사일 발사 시각
	INT nSignX, nSignY;				// 방향 처리 부호 변수
	BOSS_MISSILE_INFO BossMissile;	// 보스 미사일
	Image BossGauge;				// 보스 게이지

	BOOL BossDead;

	

	Boss();
	~Boss();

	VOID Damaged();
	VOID SetHp(INT hp);
	VOID SetPositionX(FLOAT x);

	VOID SetVisible(BOOL visible);

	VOID PatInit();

	// {보스 관련} [초기화] [업데이트] [그리기] [해제] 함수
	VOID Init();
	VOID Turn(INT a);
	VOID Update();
	VOID Draw();
	VOID Release();

	// {보스 미사일 관련} [초기화] [업데이트] [그리기] [해제] 함수
	VOID MissileInit();
	VOID MissileUpdate();
	VOID MissileDraw();
	VOID MissileRelease();


	// {보스 게이지 바 관련} [초기화] [업데이트] [그리기] [해제] 함수
	VOID GaugeInit();
	VOID GaugeUpdate();
	VOID GaugeDraw();
	VOID GaugeRelease();
};