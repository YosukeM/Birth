#pragma once

#include "SyncResourceManager.h"

class Sequence;

/**
 * 作成するアプリケーションの本体となるクラス
 */
class Application
{
	core::vector<core::shared_ptr<Sequence> > _seqs;
	core::shared_ptr<Sequence> _seq;

	void _checkExtensions();

public:
	Application();
	~Application();

	/** 毎フレーム呼ばれる関数
	 * \param delta_time 直前のフレームからの経過時間（秒）
	 */
	void update(f32 delta_time);
	
	/** ウィンドウの大きさが変わったときに呼ばれる関数
	 * \param size 
	 */
	void onResize(const uint2d& size);
	
	/** ウィンドウが閉じられようとしているときに呼ばれる関数
	 * \return 閉じてもよければtrue、そうでないときはfalse
	 */
	bool onClose();
};
