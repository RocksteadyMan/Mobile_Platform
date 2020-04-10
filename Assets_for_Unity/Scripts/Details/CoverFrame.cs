﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class CoverFrame : Detail
{
    void Start()
    {
        Name = "Рамка крышки платформы";
        Description = "Фиксирует основные детали корпуса платформы. Имеет вырез под кнопку питания.";

        pathToFollow = pathToFollow?.GetComponent<PathEditor>();
        if (pathToFollow)
        {
            pathToFollow.transform.position = transform.position;
            countOfDotsInPath = pathToFollow.pathPoints.Count;
        }
    }
}
