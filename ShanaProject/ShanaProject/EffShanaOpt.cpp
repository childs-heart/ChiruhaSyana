/********************/
/* タイトルタスク	*/
/********************/

#include "EffShanaOpt.h"
#include "EffShanaOptParts.h"
#include "CLIB_Sprite.h"
#include "ResBattle.h"

CEffShanaOpt::CEffShanaOpt( CResBattle *game, CSprite *target ):CSprite( game )
{
	// 資源調達
//	m_Anime			= game->m_AnimationManager->GetAnimation( 100 );
//	m_Tex			= game->m_TextureManager->GetTextureGroup( 100 );
	m_DispObjGroup	= m_Game->m_DispObjGroup;
	m_DispObj		= m_DispObjGroup->GetDispObj();
	m_ResBattle		= game;
//	game->m_AnimationManager->SetupAnimation( m_Anime, 0 );
//	game->m_TextureManager->SetupTextureGroup( m_Tex, 0 );

	// 初期状態
	m_Target = target;
	target->GetPosition( &m_X, &m_Y );
	m_Flame = 0;
}

CEffShanaOpt::~CEffShanaOpt()
{
	m_Game->m_DispObjGroup->FreeDispObj( m_DispObj );
}

bool CEffShanaOpt::Move()
{
	if( ( rand() % 5 ) == 0 ){
//		new(m_ResBattle->m_CommonEffectFront) CEffShanaOptParts( m_ResBattle, m_Target );
//		new(m_ResBattle->m_CommonEffectFront) CEffShanaOptParts( m_ResBattle, m_Target );
//		new(m_ResBattle->m_CommonEffectFront) CEffShanaOptParts( m_ResBattle, m_Target );
	}
	return TRUE;
}

bool CEffShanaOpt::InterfereFinalize()
{
	return TRUE;
}

bool CEffShanaOpt::Draw( CD3DDraw *draw )
{
	return TRUE;
}

bool CEffShanaOpt::DrawFinalize()
{
	return TRUE;
}
