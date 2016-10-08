using UnityEngine;
using System.Collections;

public class GyroCamera2 : MonoBehaviour {

    private Gyroscope gyro;
    private bool gyroSupported;
    private Quaternion rotfFix;

    void Start() {
        gyroSupported = SystemInfo.supportsGyroscope;

        GameObject camParent = new GameObject("cmaParent");
        camParent.transform.position = transform.position;

        transform.parent = camParent.transform;

        if (gyroSupported) {
            gyro = Input.gyro;
            gyro.enabled = true;

            camParent.transform.rotation = Quaternion.Euler(90f, 180f, 0f);
            rotfFix = new Quaternion(0, 0, 1, 0);
        }
    }

    void Update() {
        if (gyroSupported) {
            transform.localRotation = gyro.attitude * rotfFix;
        }
    }

}
