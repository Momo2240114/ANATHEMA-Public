# ANATHEMA / BigShine

ANATHEMAは、自作ゲームエンジンBigShineで制作した3Dボスバトルアクションです。このリポジトリは、展示会でエンジンとゲームの実装を確認するためのソース公開版です。C++20、Direct3D 11、HLSL、Visual Studio 2022を使用しています。

## 収録内容

- `Code/` にエンジン、Editor、ゲームのC++ソースを収録しています。
- `Shader/` にHLSLソースを収録しています。
- `Data/` にシーン、AI、入力、エフェクトなどのテキスト形式の設定を収録しています。
- Visual Studioのソリューションとプロジェクト定義を収録しています。

## 技術資料

- [エンジン全体の構成](Docs/Architecture.md)
- [GameObjectとComponent](Docs/GameObject_Component.md)
- [描画システム](Docs/Rendering.md)
- [アニメーションとActionSequence](Docs/AnimationSequence.md)
- [AIとBehavior Graph](Docs/AI_BehaviorTree.md)
- [Particle・Mesh VFXなどのエフェクト](Docs/EffectSystem.md)
- [ANATHEMAのゲームシステム](Docs/GameSystems.md)
- [主な実装箇所](Docs/CodeHighlights.md)

## 素材と動作環境

モデル・画像・テクスチャ・音声・フォント・外部SDK・ビルド成果物などは公開対象から除いています。掲載した設定には、収録していない素材への参照があります。プレイ用の配布物とは別のため、この内容だけでのビルドと起動は想定していません。開発版では別途、元の素材と `CustomExternalDependencies.props` に定義された外部ライブラリやSDKが必要です。
