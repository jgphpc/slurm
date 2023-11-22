---
marp: true
theme: cscs
# class: lead
paginate: true
backgroundColor: #fff
backgroundImage: url('https://marp.app/assets/hero-background.svg')
footer: '![width:780px](common/footer.png)'
size: 4:3
math: mathjax

---

# Outline

<br>
<br>

- Collect and send energy data with kafka plugin
- Deploy slurm
- Next steps

---
<!-- {{{ kafka -->
# Collect and send energy data (1)

```
~/slurm.git/src/plugins/jobcomp/
├── common/         <---
├── elasticsearch/
├── filetxt/
├── kafka/          <---
├── lua/
├── mysql/
├── none/
└── script/
```
---> [slurm/23-11-0-0rc1-cscs](https://github.com/SchedMD/slurm/compare/master...jgphpc:slurm:slurm-23-11-0-0rc1-cscs)

<!-- }}} -->
---
<!-- {{{ kafka -->
# Collect and send energy data (2)

```json
{
"jobid":87,
"container":null, "username":"jg", "user_id":1000, "groupname":"jg",
"group_id":1000, "@start":"2023-11-20T11:53:40", "@end":"2023-11-20T11:53:47",
"elapsed":7, "partition":"normal", "alloc_node":"jg", "nodes":"jg",
"total_cpus":4, "total_nodes":1, "derived_ec":"0:0", "exit_code":"0:0",
"state":"COMPLETED", "failed_node":null, "cpu_hours":0.0077777779661118984,
"pack_job_id":0, "pack_job_offset":0, "het_job_id":0, "het_job_offset":0,
"@submit":"2023-11-20T11:53:40", "@eligible":"2023-11-20T11:53:40",
"@queue_wait":0, "work_dir":"\/home\/jg", "qos":"normal", "ntasks":0,
"ntasks_per_node":0, "ntasks_per_tres":0, "cpus_per_task":1, "time_limit":3600,
"job_name":"sleep",

"tres_req":"cpu=1, mem=1000M, node=1, billing=1",

"tres_fmt_alloc_str":"cpu=4, mem=1000M, energy=1260, node=1, billing=4",
                                        ^^^^^^ 
"tres_alloc_str":"1=4, 2=1000, 3=1260, 4=1, 5=4"
                                 ^^^^
}
```
<!-- }}} -->
---
<!-- {{{ kafka -->
# Collect and send energy data (3)

- Compare data stored in MySQL with:
  - `sacct` -o Jobid,AllocTRES,ConsumedEnergy -j 87
```console

JobID                                           AllocTRES ConsumedEnergy
------------ -------------------------------------------- --------------
87           billing=4,cpu=4,energy=1260,mem=1000M,node=1           1260
87.0                               cpu=4,mem=1000M,node=1           1260
```
<!-- }}} -->
---
<!-- {{{ deploy -->
# Deploy slurm

- [SPCI Meeting notes:](https://confluence.cscs.ch/pages/viewpage.action?pageId=650379277)
```
Should we use Slurm provided by HPE
  According to HPE, CSCS may be breaking the "rules" by adding multi tenancy configuration
```
- M Induni, Gennaro, Riccardo: what is the process to deploy our custom version of slurm ?
<!-- }}} -->
---
<!-- {{{ next steps -->
# Next steps

- Push code back to SchedMD/HPE: open [thread](https://groups.google.com/g/slurm-users/c/P3QiMfUhews)
- Short term solution for 2023 ?
- Deploy and validate on a VCluster (which one ?)
- Compare slurm data with machine room data and/or SSA ?
- More energy data ?
- Else ?
<!-- }}} -->
---
