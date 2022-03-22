## Param Poller
An app that provides live period readings of a configurable set of parameters.

## Getting Started
This project depends on the [MAL C NMF API](https://github.com/tanagraspace/ccsdsmo-malc-sepp-apps/tree/opssat/apps/nmfapi_c); an app that's part of the [ccsdsmo-malc-sepp-apps](https://github.com/tanagraspace/ccsdsmo-malc-sepp-apps) project.

### Building
There are two ways to build the app: for local development or for the spacecraft.

#### Local Development
1. Git clone and install the [ccsdsmo-malc-sepp-apps](https://github.com/tanagraspace/ccsdsmo-malc-sepp-apps) project, invoke `./genmakeall`.
2. Change directory into the ccsdsmo-malc-sepp-apps's apps directory.
3. Add this project's repo as a git module: `git submodule add https://github.com/tanagraspace/opssat-param-poller.git param_poller`.
4. Change directory into `param_poller` and build the project by invoking `./genmake`.

### Spacecraft
Building for the spacecraft uses zproject/gsl's cross-compilation mechanism for the Raspberry Pi ARM 32 bit target environment. Using the Raspberry Pi toolchain is *not ideal* but a workable temporary solution. As a permanent solution a zproject_sepp.gsl script must be written that will cross-compile using the SEPP toolchain instead of using [zproject_rpi.gsl](https://github.com/zeromq/zproject/blob/master/zproject_rpi.gsl).

From the app's directory, execute the following commands to build and deploy the app to the spacecraft:

```bash
cd scripts
./build4targets.sh
./ipk_create.sh
./ipk_deploy.sh
```

### Configuration
- Datapool parameters can be grouped into "params" collections.
- Up to 5 groups are defined in the app's app.ini config file under the `[params]` section: params1, params2, params3, params4, and params5.
- Blank "params" groups are ignored.
- Datapool parameter values fetched for each "params" group will be written to a timestamped CSV file in the app's toGround folder, e.g. `toGround/params1_1647834954.csv`, `toGround/params2_1647834954.csv`...
- The column names of the CSV files will correspond to the name of the datapool parameters.
- Iterations and sleep time between iterations are also set in the app's app.ini config file.

e.g. Configuration in the app.ini file with some undfined params groups that will be ignored by the App:

```ini
[general]
iterations=5
sleep=2

[params]
params1=attitudeQuatA,attitudeQuatB,attitudeQuatC,attitudeQuatD
params2=CADC0884,CADC0886,CADC0888,CADC0890,CADC0892,CADC0894
params3=
params4=
params5=
```

### Running
It's a simple app that's simple to run.

#### Instructions
```bash
./src/param_poller_app --help
```

#### Execution
```bash
./src/param_poller_app
```

#### Output
- The output will be CSV files written in the app's toGround directory. 
- The CSV's `timestamp` row indicates the time in which the data was fetched.