#ifndef ALL_H
#define ALL_H

//******************************************************************************
//
//
//      all.h
//
//
//******************************************************************************

// �V�X�e���⃉�C�u�����̃w�b�_�[�t�@�C���͏�̕���
#include "../GameLib/game_lib.h"

// ���ʂŎg����悤�ȃw�b�_�[
#include "common.h"

// �X�̃w�b�_�[�t�@�C���͉��̕���
#include "audio.h"

#if 1
//******************************************************************************
// TODO:01 obj2d.h��player.h���C���N���[�h
//------------------------------------------------------------------------------
/*
�ۑ�j
    ���L��obj2d.h��player.h���C���N���[�h���܂��傤�B

����j
    �w�b�_�[�t�@�C�����C���N���[�h���鏇�Ԃ͑�؂ł��B�Ⴆ�΁Aobj2d.h��OBJ2D��
    �����\���̂��`���Ă���Aplayer.cpp��OBJ2D�^�̕ϐ���錾���邽�߁Aobj2d.h��
    ������ɗ��鎖�ɂȂ�܂��B

    ���������Ă����΁A�Ⴆ��player.h���� extern OBJ2D player; �ȂǂƏ�����悤��
    �@�Ȃ�̂ł��B
*/
//******************************************************************************
#endif
//TODO_01


#include "scene_game.h"
#include "scene_title.h"
#include "obj2d.h"  
#include "player.h"
#include "enemy.h"
#include "../consumable.h"
#include "item.h"
// namespace
using namespace GameLib;
using namespace input;


extern int x;
#endif//ALL_H
