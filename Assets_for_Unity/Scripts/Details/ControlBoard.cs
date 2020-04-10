using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class ControlBoard : Detail
{
    void Start()
    {
        Name = "Печатная плата";
        Description = "Мозгом платы является микроконтроллер ESP32. Обладает двухъядерным процессором, а также имеет встроенные Bluetooth и WiFi. Программируется в среде Arduino IDE.";

        pathToFollow = pathToFollow?.GetComponent<PathEditor>();
        if (pathToFollow)
        {
            pathToFollow.transform.position = transform.position;
            countOfDotsInPath = pathToFollow.pathPoints.Count;
        }
    }
}
