#pragma once

class Sequence;

namespace gameaudio {
	class ISound;
}

namespace rsc {
	class SyncManager;
}

/**
 * 作成するアプリケーションの本体となるクラス
 */
class Application
{
	gameaudio::ISound* _bgm;
	core::shared_ptr<rsc::SyncManager> _rm;
	core::shared_ptr<Sequence> _seq;

	void _checkExtensions();
	
	Application();

public:
	static bool hasInstance();
	static Application* instance();
	static void deleteInstance();

	~Application();

	/**
	 * 初期化
	 * Application::instance()から呼ばれるので、普通は意識しなくてもよい
	 */
	void init();

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

	// 全シーケンス共通のBGM
	gameaudio::ISound* getBGM() const;

	// リソースマネージャ
	core::shared_ptr<rsc::SyncManager> getResourceManager() const;
};
