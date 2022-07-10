# docker cmd


镜像体积
```bash
 fwz@fwz-mbp ~> docker system df
TYPE                TOTAL               ACTIVE              SIZE                RECLAIMABLE
Images              23                  0                   8.818GB             8.818GB (100%)
Containers          0                   0                   0B                  0B
Local Volumes       0                   0                   0B                  0B
Build Cache         0                   0                   0B                  0B
```

虚悬镜像
```fish
fwz@fwz-mbp ~> docker image ls -f dangling=true
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
ubuntu              <none>              20bb25d32758        2 months ago        87.5MB
```