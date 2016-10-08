using UnityEngine;
using System.Collections;

public class GyroCamera1 : MonoBehaviour {

    private Gyroscope gyro;
    private bool gyroSupported;

    void Start() {
        gyroSupported = SystemInfo.supportsGyroscope;

        if (gyroSupported) {
            gyro = Input.gyro;
            gyro.enabled = true;
        }

    }

    void Update() {
        if (gyroSupported) {
            transform.rotation = gyro.attitude;
        }
    }


}
