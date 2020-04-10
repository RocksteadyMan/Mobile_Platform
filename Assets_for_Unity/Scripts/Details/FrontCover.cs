using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class FrontCover : Detail
{
    void Start()
    {
        Name = "Задний борт платформы";
        Description = "Имеет отверстие под УЗ-датчик. Благодаря специальным разрезам по краям имеет гибкую форму.";

        pathToFollow = pathToFollow?.GetComponent<PathEditor>();
        if (pathToFollow)
        {
            pathToFollow.transform.position = transform.position;
            countOfDotsInPath = pathToFollow.pathPoints.Count;
        }
    }
}
