#pragma once

#include "Color.h"

/**
 * 画面遷移を作るための基本クラス。
 * サブクラスのためにいくつかの便利機能を提供している。
 */
class Sequence {
private:
	f32 _fadeTimer, _fadeDuration;
	Color _fadeColor;
public:
	typedef enum {
		EFS_NONE,
		EFS_FADEIN,
		EFS_FADEOUT
	} EFadeState;
private:
	EFadeState _fadeState;

	void _drawFading(f32);

protected:
	Sequence();

	// フェードインを開始する。
	// \param duration フェードインが完了するまでの時間
	// \param from 開始時のフェードインの色
	void _fadein(f32 duration = 1.0f, const Color& from = Color(0x000000FF));

	// フェードアウトを開始し、シーケンスを終了させる
	// \param duration フェードアウトが完了するまでの時間
	// \param to 終了時の画面の色
	void _fadeout(f32 duration = 1.0f, const Color& to = Color(0x000000FF));

	// 今どのようにフェードしているか取得する。
	// \return EFS_NONE | EFS_FADEIN | EFS_FADEOUT
	EFadeState _getFadeState() const;

	// フェーディングの進行状況を取得する。
	// FADEIN時は1から0へ、FADEOUT時は0から1へ推移する値が得られる。
	float _getFadeLevel() const;

	// サブクラスが実装すべき関数
	virtual void _draw() = 0;
	virtual void _update(f32) = 0;
	virtual core::shared_ptr<Sequence> _getNextSequence() = 0;

public:
	virtual ~Sequence();

	// 毎フレーム呼ぶ更新関数
	// \param delta_time 直前のフレームからの経過時間
	// \return 次のシーケンス（遷移がなければnull）
	core::shared_ptr<Sequence> update(f32 delta_time);

	// 毎フレーム呼ぶ描画関数
	void draw();

	// 画面サイズ変更時に呼ぶ関数
	virtual void onResize(const uint2d& size) {};
};