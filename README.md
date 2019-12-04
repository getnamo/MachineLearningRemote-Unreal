# machine-learning-remote-ue4
Machine Learning plugin for the Unreal Engine, encapsulating calls to remote python servers running Tensorflow.

Should have the same api as tensorflow-ue4, but with freedom to run a host server on platform of choice (e.g. remote win/linux/mac instances).

## Machine Learning Plugin Variants

Want to run tensorflow or pytorch on a remote python server?

- https://github.com/getnamo/machine-learning-remote-ue4

Want to use tensorflow python api embedded in your unreal engine project? 

- https://github.com/getnamo/tensorflow-ue4

Want native tensorflow inference? (WIP)

- https://github.com/getnamo/tensorflow-native-ue4

## Quick Install & Setup

1. Install https://github.com/getnamo/ml-remote-server on your target backend (can be a local folder)
2. Download [Latest Release](https://github.com/getnamo/machine-learning-remote-ue4/releases)
3. Create new or choose project.
4. Browse to your project folder (typically found at Documents/Unreal Project/{Your Project Root})
5. Copy Plugins folder into your Project root.
6. Plugin should be now ready to use. Remember to startup your [server](https://github.com/getnamo/ml-remote-server) when using this plugin. 

## Status
Not yet functional see https://github.com/getnamo/tensorflow-remote-ue4/issues/1 for initial build status.
