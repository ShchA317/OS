# Лабораторная работа №1



### cpu testing

выданные параметры: float80, float128

необходимо добиться максимальной производительности системы


в документации stree-ng написано:

> bogo ops number of iterations of the stressor during the run. This is metric of how much overall "work" has been achieved in bogo operations.  Do not use this as a reliable measure of throughput for benchmarking.

но, так как опираться нам больше не на что, то возьмем за основу то что есть, то есть показатель `bogo ops` а для получения заветных FLOPS будем умножать полученное значение на 1000, т.к. stress-ng приводит нагрузку батчами по 1000 итераций для параметров float80 и float128

параметры процессора, используемого в тесте можно получить с помощью `lscpu`. В моем случае это:

```
Architecture:            x86_64
  CPU op-mode(s):        32-bit, 64-bit
  Address sizes:         39 bits physical, 48 bits virtual
  Byte Order:            Little Endian
CPU(s):                  4
  On-line CPU(s) list:   0-3
Vendor ID:               GenuineIntel
  Model name:            Intel(R) Core(TM) i3-1005G1 CPU @ 1.20GHz
    CPU family:          6
    Model:               126
    Thread(s) per core:  2
    Core(s) per socket:  2
    Socket(s):           1
    Stepping:            5
    CPU(s) scaling MHz:  22%
    CPU max MHz:         3400.0000
    CPU min MHz:         400.0000
    BogoMIPS:            2381.00
    Flags:               fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat 
                         pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx p
                         dpe1gb rdtscp lm constant_tsc art arch_perfmon pebs bts rep_good n
                         opl xtopology nonstop_tsc cpuid aperfmperf tsc_known_freq pni pclm
                         ulqdq dtes64 monitor ds_cpl vmx est tm2 ssse3 sdbg fma cx16 xtpr p
                         dcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes 
                         xsave avx f16c rdrand lahf_lm abm 3dnowprefetch cpuid_fault epb in
                         vpcid_single ssbd ibrs ibpb stibp ibrs_enhanced tpr_shadow flexpri
                         ority ept vpid ept_ad fsgsbase tsc_adjust sgx bmi1 avx2 smep bmi2 
                         erms invpcid avx512f avx512dq rdseed adx smap avx512ifma clflushop
                         t intel_pt avx512cd sha_ni avx512bw avx512vl xsaveopt xsavec xgetb
                         v1 xsaves split_lock_detect dtherm ida arat pln pts hwp hwp_notify
                          hwp_act_window hwp_epp hwp_pkg_req vnmi avx512vbmi umip pku ospke
                          avx512_vbmi2 gfni vaes vpclmulqdq avx512_vnni avx512_bitalg avx51
                         2_vpopcntdq rdpid sgx_lc fsrm md_clear flush_l1d arch_capabilities
Virtualization features: 
  Virtualization:        VT-x
Caches (sum of all):     
  L1d:                   96 KiB (2 instances)
  L1i:                   64 KiB (2 instances)
  L2:                    1 MiB (2 instances)
  L3:                    4 MiB (1 instance)
NUMA:                    
  NUMA node(s):          1
  NUMA node0 CPU(s):     0-3
Vulnerabilities:         
  Gather data sampling:  Mitigation; Microcode
  Itlb multihit:         KVM: Mitigation: VMX disabled
  L1tf:                  Not affected
  Mds:                   Not affected
  Meltdown:              Not affected
  Mmio stale data:       Mitigation; Clear CPU buffers; SMT vulnerable
  Retbleed:              Mitigation; Enhanced IBRS
  Spec rstack overflow:  Not affected
  Spec store bypass:     Mitigation; Speculative Store Bypass disabled via prctl
  Spectre v1:            Mitigation; usercopy/swapgs barriers and __user pointer sanitizati
                         on
  Spectre v2:            Mitigation; Enhanced / Automatic IBRS, IBPB conditional, RSB filli
                         ng, PBRSB-eIBRS SW sequence
  Srbds:                 Mitigation; Microcode
  Tsx async abort:       Not affected
```

в процессе выполнения нам важно понимать, на сколько загружается каждое из ядер процессора для мониторинга этого параметра можно использовать

```bash
watch -n0.1 "grep Hz /proc/cpuinfo"
```

для мониторинга нагрузки на каждое их ядер процессора можно воспользоваться утилитой `htop` или стандартной `top`


для уменьшения влияния работающих программ на результаты тестов были "убиты" все не относящиеся к выполнению лабораторной работы процессы.

увидеть результаты массового убийства процессов можно с помощью утилиты `ps`, вызвав её с ключом -A. Полученный результат:

```
   PID TTY          TIME CMD
      1 ?        00:00:03 systemd
      2 ?        00:00:00 kthreadd
      3 ?        00:00:00 rcu_gp
      4 ?        00:00:00 rcu_par_gp
      5 ?        00:00:00 slub_flushwq
      6 ?        00:00:00 netns
      8 ?        00:00:00 kworker/0:0H-events_highpri
     11 ?        00:00:00 mm_percpu_wq
     13 ?        00:00:00 rcu_tasks_kthread
     14 ?        00:00:00 rcu_tasks_rude_kthread
     15 ?        00:00:00 rcu_tasks_trace_kthread
     16 ?        00:01:03 ksoftirqd/0
     17 ?        00:00:19 rcu_preempt
     18 ?        00:00:00 rcub/0
     19 ?        00:00:00 migration/0
     20 ?        00:00:00 idle_inject/0
     21 ?        00:00:00 cpuhp/0
     22 ?        00:00:00 cpuhp/1
     23 ?        00:00:00 idle_inject/1
     24 ?        00:00:00 migration/1
     25 ?        00:00:03 ksoftirqd/1
     27 ?        00:00:00 kworker/1:0H-events_highpri
     28 ?        00:00:00 cpuhp/2
     29 ?        00:00:00 idle_inject/2
     30 ?        00:00:00 migration/2
     31 ?        00:00:02 ksoftirqd/2
     33 ?        00:00:00 kworker/2:0H-events_highpri
     34 ?        00:00:00 cpuhp/3
     35 ?        00:00:00 idle_inject/3
     36 ?        00:00:00 migration/3
     37 ?        00:00:02 ksoftirqd/3
     39 ?        00:00:00 kworker/3:0H-events_highpri
     40 ?        00:00:00 kdevtmpfs
     41 ?        00:00:00 inet_frag_wq
     42 ?        00:00:00 kauditd
     43 ?        00:00:00 khungtaskd
     44 ?        00:00:00 oom_reaper
     46 ?        00:00:00 writeback
     47 ?        00:00:02 kcompactd0
     48 ?        00:00:00 ksmd
     50 ?        00:00:03 khugepaged
     51 ?        00:00:00 kintegrityd
     52 ?        00:00:00 kblockd
     53 ?        00:00:00 blkcg_punt_bio
     56 ?        00:00:00 tpm_dev_wq
     57 ?        00:00:00 ata_sff
     58 ?        00:00:00 edac-poller
     59 ?        00:00:00 devfreq_wq
     60 ?        00:00:00 watchdogd
     61 ?        00:00:00 kworker/3:1H-kblockd
     62 ?        00:00:00 ksgxd
     63 ?        00:00:00 kswapd0
     64 ?        00:00:00 kthrotld
     65 ?        00:00:00 acpi_thermal_pm
     68 ?        00:00:02 hwrng
     69 ?        00:00:00 scsi_eh_0
     70 ?        00:00:00 scsi_tmf_0
     71 ?        00:00:00 mld
     72 ?        00:00:00 kworker/2:1H-events_highpri
     73 ?        00:00:00 ipv6_addrconf
     80 ?        00:00:00 kstrp
     81 ?        00:00:00 zswap-shrink
     82 ?        00:00:00 kworker/u9:0-rb_allocator
     83 ?        00:00:00 charger_manager
    125 ?        00:00:00 kworker/1:1H-kblockd
    126 ?        00:00:00 kworker/0:1H-kblockd
    127 ?        00:00:00 nvme-wq
    128 ?        00:00:00 nvme-reset-wq
    129 ?        00:00:00 nvme-delete-wq
    130 ?        00:00:00 nvme-auth-wq
    146 ?        00:00:02 jbd2/nvme0n1p2-8
    147 ?        00:00:00 ext4-rsv-conver
    184 ?        00:00:01 systemd-journal
    229 ?        00:00:00 systemd-udevd
    230 ?        00:00:00 psimon
    231 ?        00:00:00 systemd-network
    276 ?        00:00:00 cfg80211
    282 ?        00:00:14 jbd2/nvme0n1p3-8
    283 ?        00:00:00 ext4-rsv-conver
    292 ?        00:00:54 irq/48-MSFT0001:01
    296 ?        00:00:04 irq/130-iwlwifi:default_queue
    297 ?        00:00:02 irq/131-iwlwifi:queue_1
    298 ?        00:00:02 irq/132-iwlwifi:queue_2
    299 ?        00:00:01 irq/133-iwlwifi:queue_3
    300 ?        00:00:02 irq/134-iwlwifi:queue_4
    301 ?        00:00:00 irq/135-iwlwifi:exception
    302 ?        00:00:00 irq/136-mei_me
    321 ?        00:00:00 cryptd
    323 ?        00:00:08 systemd-resolve
    324 ?        00:00:00 systemd-timesyn
    335 ?        00:00:00 dbus-daemon
    336 ?        00:00:00 systemd-logind
    341 ?        00:05:41 containerd
    344 ?        00:00:00 ttm
    364 ?        00:00:00 card1-crtc0
    365 ?        00:00:00 card1-crtc1
    366 ?        00:00:00 card1-crtc2
    381 ?        00:00:00 lightdm
    393 tty7     01:17:10 Xorg
    480 ?        00:00:00 lightdm
    488 ?        00:00:00 systemd
    489 ?        00:00:00 (sd-pam)
    495 ?        00:23:22 pipewire
    496 ?        00:00:02 wireplumber
    497 ?        00:31:21 pipewire-pulse
    498 ?        00:00:06 i3
    504 ?        00:00:00 dbus-daemon
    535 ?        00:04:26 polybar
    539 ?        00:24:22 picom
    555 ?        00:05:16 terminator
    556 ?        00:00:00 at-spi-bus-laun
    563 ?        00:00:00 dbus-daemon
    584 ?        00:00:05 at-spi2-registr
    616 ?        00:00:00 wpa_supplicant
    953 ?        00:00:00 polkitd
   1118 pts/3    00:00:05 fish
  36477 pts/0    00:00:00 fish
  36496 pts/0    00:07:07 htop
  36513 pts/1    00:00:00 fish
  36984 pts/4    00:00:00 fish
  37483 pts/5    00:00:00 fish
  37517 pts/5    00:00:08 vim
  45020 pts/2    00:00:00 fish
  45114 pts/2    00:00:00 bat
  45116 pts/2    00:00:00 less
  48879 ?        00:00:00 kworker/u9:2-rb_allocator
  50067 pts/7    00:00:00 fish
  84223 ?        00:00:01 kworker/u8:0-flush-259:0
  85354 ?        00:00:01 kworker/u8:1-flush-259:0
  89736 pts/6    00:00:00 fish
  89788 ?        00:00:00 kworker/2:2-events
  92846 ?        00:00:00 psimon
  93241 ?        00:00:00 kworker/1:1-i915-unordered
  93613 pts/4    00:00:00 man
  93620 pts/4    00:00:00 man
  93621 pts/4    00:00:00 less
  95400 ?        00:00:00 kworker/u8:3-events_unbound
  97344 ?        00:00:00 kworker/u8:2-events_unbound
  97558 ?        00:00:00 kworker/0:2-i915-unordered
  97670 ?        00:00:00 kworker/3:2-events
  98534 ?        00:00:00 kworker/3:0-events
  98571 ?        00:00:00 kworker/0:1-i915-unordered
  98579 ?        00:00:00 kworker/2:1-rcu_gp
  98655 ?        00:00:00 kworker/1:2-events
  98707 ?        00:00:00 kworker/0:0-i915-unordered
  99005 ?        00:00:00 kworker/2:0-rcu_gp
  99089 ?        00:00:00 kworker/1:0-inet_frag_wq
  99125 ?        00:00:00 kworker/3:1-rcu_gp
  99126 ?        00:00:00 kworker/0:3-events
  99401 ?        00:00:00 kworker/2:3
  99402 ?        00:00:00 kworker/2:4-rcu_gp
  99403 ?        00:00:00 kworker/u8:4-events_unbound
  99463 ?        00:00:00 kworker/1:3-events
  99541 pts/6    00:00:00 ps
```


#### Выполнение тестирования

запустим десятисекундный тест с float80 арифметикой для двух ядер:

```
# stress-ng --cpu 2 --cpu-method float80 --metrics --timeout 10

stress-ng: info:  [2565] setting to a 10 secs run per stressor
stress-ng: info:  [2565] dispatching hogs: 2 cpu
stress-ng: metrc: [2565] stressor       bogo ops real time  usr time  sys time   bogo ops/s     bogo ops/s CPU used per       RSS Max
stress-ng: metrc: [2565]                           (secs)    (secs)    (secs)   (real time) (usr+sys time) instance (%)          (KB)
stress-ng: metrc: [2565] cpu               33245     10.00     19.90      0.00      3324.39        1670.57        99.50          4896
stress-ng: info:  [2565] skipped: 0
stress-ng: info:  [2565] passed: 2: cpu (2)
stress-ng: info:  [2565] failed: 0
stress-ng: info:  [2565] metrics untrustworthy: 0
stress-ng: info:  [2565] successful run completed in 10.00 secs
```

Запустим тест несколько раз для того, чтобы убедиться в воспроизводимости резултата. Затем для сравнения 

В момент нагрузки иммеем максимальную частоту процессора на всех ядрах в течение всего теста.

```
# watch -n1 "grep Hz /proc/cpuinfo"

Every 0.01s: grep Hz /proc/cpuinfo                       archlinux: Mon Oct 16 11:12:11 2023

model name      : Intel(R) Core(TM) i3-1005G1 CPU @ 1.20GHz
cpu MHz         : 3399.981
model name      : Intel(R) Core(TM) i3-1005G1 CPU @ 1.20GHz
cpu MHz         : 3400.000
model name      : Intel(R) Core(TM) i3-1005G1 CPU @ 1.20GHz
cpu MHz         : 3400.000
model name      : Intel(R) Core(TM) i3-1005G1 CPU @ 1.20GHz
cpu MHz         : 3400.000
```

В это время в `top` наблюдаем 

```
top - 11:28:53 up 30 min,  1 user,  load average: 0.98, 0.47, 0.33
Tasks: 157 total,   1 running, 156 sleeping,   0 stopped,   0 zombie
%Cpu0  :  0.3 us,  0.0 sy,  0.0 ni, 99.3 id,  0.0 wa,  0.0 hi,  0.3 si,  0.0 st 
%Cpu1  : 97.4 us,  0.0 sy,  0.0 ni,  3.6 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st 
%Cpu2  : 97.3 us,  0.0 sy,  0.0 ni,  3.7 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st 
%Cpu3  :  1.0 us,  0.3 sy,  0.0 ni, 98.7 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st 
```

в результате выполнения эксперимента было утсановлено, что наибольшую производительность процессор показывает при использовании всех 4-х виртуальных ядер.


```bash
# stress-ng --cpu 4 --cpu-method float80 --metrics --timeout 10
stress-ng: info:  [7023] setting to a 10 secs run per stressor
stress-ng: info:  [7023] dispatching hogs: 4 cpu
stress-ng: metrc: [7023] stressor       bogo ops real time  usr time  sys time   bogo ops/s     bogo ops/s CPU used per       RSS Max
stress-ng: metrc: [7023]                           (secs)    (secs)    (secs)   (real time) (usr+sys time) instance (%)          (KB)
stress-ng: metrc: [7023] cpu               48518     10.00     39.56      0.01      4851.63        1226.00        98.93          4892
stress-ng: info:  [7023] skipped: 0
stress-ng: info:  [7023] passed: 4: cpu (4)
stress-ng: info:  [7023] failed: 0
stress-ng: info:  [7023] metrics untrustworthy: 0
stress-ng: info:  [7023] successful run completed in 10.01 secs
```

аналогично для float128:

```bash
# stress-ng --cpu 4 --cpu-method float128 --metrics --timeout 10
stress-ng: info:  [7478] setting to a 10 secs run per stressor
stress-ng: info:  [7478] dispatching hogs: 4 cpu
]stress-ng: metrc: [7478] stressor       bogo ops real time  usr time  sys time   bogo ops/s     bogo ops/s CPU used per       RSS Max
stress-ng: metrc: [7478]                           (secs)    (secs)    (secs)   (real time) (usr+sys time) instance (%)          (KB)
stress-ng: metrc: [7478] cpu               45571     10.00     39.74      0.01      4556.90        1146.29        99.38          5024
stress-ng: info:  [7478] skipped: 0
stress-ng: info:  [7478] passed: 4: cpu (4)
stress-ng: info:  [7478] failed: 0
stress-ng: info:  [7478] metrics untrustworthy: 0
stress-ng: info:  [7478] successful run completed in 10.00 secs
```


### cache testing

из документации stress-ng:

> --l1cache N
                   start N workers that exercise the CPU level 1 cache with reads and writes. A cache aligned buffer that is twice the level 1 cache size is read and then written in level 1 cache set sized steps over each  level  1 \
                   cache set. This is designed to exercise cache block evictions. The bogo-op count measures the number of million cache lines touched.  Where possible, the level 1 cache geometry is determined from the kernel, how‐ \
                   ever, this is not possible on some architectures or kernels, so one may need to specify these manually. One can specify 3 out of the 4 cache geometric parameters, these are as follows: ....




лучшие результаты при тестирвоании кэша на пятисекундном отрезке были получены при использовании двух "воркеров":

```
# stress-ng --l1cache 2 --metrics --timeout 5
stress-ng: info:  [9325] setting to a 5 secs run per stressor
stress-ng: info:  [9325] dispatching hogs: 2 l1cache
stress-ng: info:  [9326] l1cache: l1cache: size: 48.0K, sets: 64, ways: 12, line size: 64 bytes
stress-ng: metrc: [9325] stressor       bogo ops real time  usr time  sys time   bogo ops/s     bogo ops/s CPU used per       RSS Max
stress-ng: metrc: [9325]                           (secs)    (secs)    (secs)   (real time) (usr+sys time) instance (%)          (KB)
stress-ng: metrc: [9325] l1cache            6400      5.07     10.14      0.00      1261.65         631.36        99.92          2720
stress-ng: info:  [9325] skipped: 0
stress-ng: info:  [9325] passed: 2: l1cache (2)
stress-ng: info:  [9325] failed: 0
stress-ng: info:  [9325] metrics untrustworthy: 0
stress-ng: info:  [9325] successful run completed in 5.09 secs
```

для большего охвата кэша во время теста оказалось эффективным уменьшить line-size до двух байтов:

```
# stress-ng --l1cache 2 --l1cache-line-size 2 --metrics --timeout 5
stress-ng: info:  [11810] setting to a 5 secs run per stressor
stress-ng: info:  [11810] dispatching hogs: 2 l1cache
stress-ng: info:  [11811] l1cache: l1cache: size: 48.0K, sets: 2048, ways: 12, line size: 2 bytes
stress-ng: metrc: [11810] stressor       bogo ops real time  usr time  sys time   bogo ops/s     bogo ops/s CPU used per       RSS Max
stress-ng: metrc: [11810]                           (secs)    (secs)    (secs)   (real time) (usr+sys time) instance (%)          (KB)
stress-ng: metrc: [11810] l1cache            8192      5.61     11.20      0.00      1461.10         731.11        99.92          2720
stress-ng: info:  [11810] skipped: 0
stress-ng: info:  [11810] passed: 2: l1cache (2)
stress-ng: info:  [11810] failed: 0
stress-ng: info:  [11810] metrics untrustworthy: 0
stress-ng: info:  [11810] successful run completed in 5.61 secs
```




