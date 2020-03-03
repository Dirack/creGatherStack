# cre-gather-interpolation (Madagascar)

[Developed to Madagascar package, version 2.0.](http://www.ahay.org/wiki/Main_Page)

> Common Reflection Element (CRE) Gather interpolation using adaptative 
> pretitive error filters (PEF) and Very Fast Simulated Aneeling (VFSA) global optimization.

A set of seismic traces that belong to a specific CRE trajectory, for a given RNIP and BETA form a CRE Gather:
So, CRE Gather interpolation algorithm uses Very Fast Simulated Anneling (VFSA) global optimization 
in order to get RNIP and BETA parameters to calculate CRE trajectory. Also increase data sampling, 
interpolating original seismic data with adaptative preditive error filters (PEF). 
Get all traces in the interpolated seismic data that belong to the CRE trajectory previously calculated.

![Interpolated CRE Gather](https://github.com/Dirack/cre-gather-interpolation/blob/master/images/creCurveInterp.png)

#### Main program algorithm



![Main program algorithm](https://github.com/Dirack/cre-gather-interpolation/blob/feature/mainDiagram/diagrams/mainDiagram.png)

