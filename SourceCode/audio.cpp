#include "all.h"

//--------------------------------------
//  オーディオの初期設定
//--------------------------------------
void audio_init()
{
    // 音楽の読み込み
    music::load(0, L"./Data/Musics/theme.wav");
    music::load(1, L"./Data/Musics/MUSIC.wav");
    sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");    // メニューなどのSE
    sound::load(XWB_STAGE1, L"./Data/Sounds/stage1.xwb");    // ステージ用のSE
    sound::load(4, L"./Data/Sounds/wadaheck.xwb");
    sound::setVolume(XWB_STAGE1, XWB_STAGE1_JUMP, 0.1f);
    sound::setVolume(4,0, 0.25f);
}

//--------------------------------------
//  オーディオの終了処理
//--------------------------------------
void audio_deinit()
{
    // 音楽を全て解放
    music::clear();
}
