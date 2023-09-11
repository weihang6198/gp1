#include "all.h"

//--------------------------------------
//  �I�[�f�B�I�̏����ݒ�
//--------------------------------------
void audio_init()
{
    // ���y�̓ǂݍ���
    music::load(0, L"./Data/Musics/theme.wav");
    music::load(1, L"./Data/Musics/MUSIC.wav");
    sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");    // ���j���[�Ȃǂ�SE
    sound::load(XWB_STAGE1, L"./Data/Sounds/stage1.xwb");    // �X�e�[�W�p��SE
    sound::load(4, L"./Data/Sounds/wadaheck.xwb");
    sound::setVolume(XWB_STAGE1, XWB_STAGE1_JUMP, 0.1f);
    sound::setVolume(4,0, 0.25f);
}

//--------------------------------------
//  �I�[�f�B�I�̏I������
//--------------------------------------
void audio_deinit()
{
    // ���y��S�ĉ��
    music::clear();
}
