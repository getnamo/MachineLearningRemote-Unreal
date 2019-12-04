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

## How to use

### Python API
These scripts should be placed in your https://github.com/getnamo/ml-remote-server ```scripts``` folder. If a matching script is defined in your ```MachineLearningRemote```->```DefaultScript``` property it should load on connect.

Keep in mind that ```tensorflow``` is optional and used as an illustrative example of ML, you can use any other valid python library e.g. pytorch instead without issue.

#### empty_example
```python
import tensorflow as tf
from mlpluginapi import MLPluginAPI

class ExampleAPI(MLPluginAPI):

	#optional api: setup your model for training
	def on_setup(self):
		pass
		
	#optional api: parse input object and return a result object, which will be converted to json for UE4
	def on_json_input(self, input):
		result = {}
		return result

	#optional api: start training your network
	def on_begin_training(self):
		pass


#NOTE: this is a module function, not a class function. Change your CLASSNAME to reflect your class
#required function to get our api
def get_api():
	#return CLASSNAME.getInstance()
	return ExampleAPI.get_instance()
```
#### add_example
```python
import tensorflow as tf
from mlpluginapi import MLPluginAPI

class ExampleAPI(MLPluginAPI):

	#expected optional api: setup your model for training
	def on_setup(self):
		self.sess = tf.InteractiveSession()
		#self.graph = tf.get_default_graph()

		self.a = tf.placeholder(tf.float32)
		self.b = tf.placeholder(tf.float32)

		#operation
		self.c = self.a + self.b

		print('setup complete')
		pass
		
	#expected optional api: parse input object and return a result object, which will be converted to json for UE4
	def on_json_input(self, jsonInput):
		
		print(jsonInput)

		feed_dict = {self.a: jsonInput['a'], self.b: jsonInput['b']}

		rawResult = self.sess.run(self.c, feed_dict)

		print('raw result: ' + str(rawResult))

		return {'c':rawResult.tolist()}

	#custom function to change the op
	def change_operation(self, type):
		if(type == '+'):
			self.c = self.a + self.b

		elif(type == '-'):
			self.c = self.a - self.b
		print('operation changed to ' + type)


	#expected optional api: start training your network
	def on_begin_training(self):
		pass
    
#NOTE: this is a module function, not a class function. Change your CLASSNAME to reflect your class
#required function to get our api
def get_api():
	#return CLASSNAME.get_instance()
	return ExampleAPI.get_instance()
```

## Status
Not yet functional see https://github.com/getnamo/tensorflow-remote-ue4/issues/1 for initial build status.
