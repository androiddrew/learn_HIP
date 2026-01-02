# Hello HIP

This is a bit more than the standard helloWorld.




## Profiling

Its nice that we can see our application producing some output but we want to "ensure" that this is indeed running on the GPU. You can do that by using the `rocprofv3` tool.


```
toor@warpspace:~/workspace/learn_HIP/helloworld$ make profile
rocprofv3 --kernel-trace --stats --output-format csv -d ./profileResults -- ./helloWorld
W20260102 09:53:32.650377 129017998229312 simple_timer.cpp:55] [rocprofv3] tool initialization ::     0.000324 sec
W20260102 09:53:32.650548 129017998229312 simple_timer.cpp:55] [rocprofv3] './helloWorld' ::     0.000000 sec
W20260102 09:53:32.659294 129017998229312 tool.cpp:2420] HSA version 8.19.1 initialized (instance=0)
Running on: AMD Radeon AI PRO R9700
Compute Capability: 12.0
Hello GPU programming! Block: 0, Thread: 0
Hello GPU programming! Block: 0, Thread: 1
Hello GPU programming! Block: 0, Thread: 2
Hello GPU programming! Block: 0, Thread: 3
Hello GPU programming! Block: 1, Thread: 0
Hello GPU programming! Block: 1, Thread: 1
Hello GPU programming! Block: 1, Thread: 2
Hello GPU programming! Block: 1, Thread: 3
Hello GPU programming! Block: 3, Thread: 0
Hello GPU programming! Block: 3, Thread: 1
Hello GPU programming! Block: 3, Thread: 2
Hello GPU programming! Block: 3, Thread: 3
Hello GPU programming! Block: 2, Thread: 0
Hello GPU programming! Block: 2, Thread: 1
Hello GPU programming! Block: 2, Thread: 2
Hello GPU programming! Block: 2, Thread: 3
Kernel executed and synchronized successfully.
W20260102 09:53:32.736123 129017998229312 simple_timer.cpp:55] [rocprofv3] './helloWorld' ::     0.085575 sec
E20260102 09:53:32.744880 129017998229312 output_stream.cpp:111] Opened result file: ./profileResults/warpspace/38816_kernel_stats.csv
E20260102 09:53:32.744980 129017998229312 output_stream.cpp:111] Opened result file: ./profileResults/warpspace/38816_kernel_trace.csv
E20260102 09:53:32.747086 129017998229312 output_stream.cpp:111] Opened result file: ./profileResults/warpspace/38816_agent_info.csv
E20260102 09:53:32.747163 129017998229312 output_stream.cpp:111] Opened result file: ./profileResults/warpspace/38816_domain_stats.csv
W20260102 09:53:32.747912 129017998229312 simple_timer.cpp:55] [rocprofv3] output generation ::     0.011168 sec
W20260102 09:53:32.747932 129017998229312 simple_timer.cpp:55] [rocprofv3] tool finalization ::     0.011212 sec

```

This output should be enough to prove to you that the program indeed is running on the GPU. Take a look at the profile output filse a we can see the number of times that our kernel was dispatched.


```text
toor@warpspace:~/workspace/learn_HIP/helloworld$ cat profileResults/warpspace/38816_kernel_stats.csv 
"Name","Calls","TotalDurationNs","AverageNs","Percentage","MinNs","MaxNs","StdDev"
"gpuHello()",1,105280,105280.000000,100.00,105280,105280,0.00000000e+00
```

```text
toor@warpspace:~/workspace/learn_HIP/helloworld$ cat ./profileResults/warpspace/38816_
38816_agent_info.csv    38816_domain_stats.csv  38816_kernel_stats.csv  38816_kernel_trace.csv  
toor@warpspace:~/workspace/learn_HIP/helloworld$ cat ./profileResults/warpspace/38816_kernel_trace.csv 
"Kind","Agent_Id","Queue_Id","Stream_Id","Thread_Id","Dispatch_Id","Kernel_Id","Kernel_Name","Correlation_Id","Start_Timestamp","End_Timestamp","LDS_Block_Size","Scratch_Size","VGPR_Count","Accum_VGPR_Count","SGPR_Count","Workgroup_Size_X","Workgroup_Size_Y","Workgroup_Size_Z","Grid_Size_X","Grid_Size_Y","Grid_Size_Z"
"KERNEL_DISPATCH","Agent 1",1,0,38816,1,1,"gpuHello()",1,143195244785252,143195244890532,0,0,40,0,128,4,1,1,16,1,1
```
