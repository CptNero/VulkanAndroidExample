# VulkanAndroidExample

Android port of the VulkanTutorial example.

### Android build
Just open the android folder in Android Studio or
```shell
# Configuring Android sdk and ndk is a requirement
# I recommend using a local.properties file with the following line
# sdk.dir=<path-to-android-sdk-folder>
cd android
bash gradlew assembleDebug
```
and then install the apk via adb.
