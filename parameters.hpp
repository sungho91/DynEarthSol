#ifndef DYNEARTHSOL3D_PARAMETERS_HPP
#define DYNEARTHSOL3D_PARAMETERS_HPP

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

#include "constants.hpp"
#include "array2d.hpp"

typedef std::pair<double,double> double_pair;
typedef std::unordered_map<int,int> int_map;
typedef std::vector<int_map> int_map2D;

typedef std::vector<double> double_vec;
typedef std::vector<int> int_vec;
typedef std::vector<int_vec> int_vec2D;
typedef std::vector<uint> uint_vec;

typedef Array2D<double,NDIMS> array_t;
typedef Array2D<double,NSTR> tensor_t;
typedef Array2D<double,NODES_PER_ELEM> shapefn;
typedef Array2D<double,1> regattr_t;
typedef Array2D<double,NODES_PER_ELEM*3> elem_cache;
typedef Array2D<double,2> dh_t;

typedef Array2D<int,NODES_PER_ELEM> conn_t;
typedef Array2D<int,NDIMS> segment_t;
typedef Array2D<int,1> segflag_t;
typedef Array2D<int,NODES_PER_CELL> regular_t;

// forward declaration
class PhaseChange;


//
// Structures for input parameters
//
struct Sim {
    double max_time_in_yr;
    double output_time_interval_in_yr;
    int max_steps;
    int output_step_interval;
    int checkpoint_frame_interval;
    int restarting_from_frame;
    bool is_outputting_averaged_fields;
    bool is_restarting;
    bool has_initial_checkpoint;
    bool has_output_during_remeshing;
    bool has_marker_output;

    std::string modelname;
    std::string restarting_from_modelname;
};

struct Mesh {
    int meshing_option;
    int meshing_elem_shape;
    int meshing_verbosity;
    bool meshing_sediment;
    int tetgen_optlevel;
    int quality_check_step_interval;

    double xlength, ylength, zlength;
    double resolution;
    double smallest_size;
    double largest_size;
    double sediment_size;
    double min_angle;  // for 2D only
    double min_tet_angle, max_ratio; // for 3D only
    double min_quality;
    double max_boundary_distortion;

    double_pair refined_zonex, refined_zoney, refined_zonez;
    std::string poly_filename;
    std::string exo_filename;

    bool is_discarding_internal_segments;
    int remeshing_option;

    // Parameters for mesh optimizer MMG
    int mmg_debug;
    int mmg_verbose;
    double mmg_hmax_factor;
    double mmg_hmin_factor;
    double mmg_hausd_factor;
};

struct Control {
    double gravity;
    double characteristic_speed;
    double inertial_scaling;
    double dt_fraction;
    double fixed_dt;
    double damping_factor;
    int damping_option;
    int ref_pressure_option;
//    bool surface_pressure_correction;
    bool is_using_mixed_stress;
    double mixed_stress_reference_viscosity;

    int surface_process_option;
    double surface_diffusivity;
    double surf_diff_ratio_terrig;
    double surf_diff_ratio_marine;
    double surf_depo_universal;
    double surf_base_level;
    double terrig_sediment_volume;
    double terrig_sediment_area;
    double terrig_sediment_diffusivity;
    double terrig_depth_coefficient;
    bool is_reporting_terrigenous_info;
    double hemipelagic_sedimentation_rate;
    double hemipelagic_width;
    double hemipelagic_max_depth;
    double pelagic_sedimentation_rate;
    double pelagic_increasing_width;

    bool is_quasi_static;
    bool has_thermal_diffusion;
    bool has_hydraulic_diffusion;

    bool has_hydration_processes;
    double hydration_migration_speed;

    bool has_PT;
    mutable bool PT_jump;
    int PT_max_iter;
    double PT_relative_tolerance;

    bool has_moving_mesh;
    bool has_ATS;

};

struct BC {
    double surface_temperature;
    double mantle_temperature;

    double winkler_delta_rho;
    bool has_winkler_foundation;

    double elastic_foundation_constant;
    bool has_elastic_foundation;

    bool has_water_loading;

    int vbc_x0;
    int vbc_x1;
    int vbc_y0;
    int vbc_y1;
    int vbc_z0;
    int vbc_z1;
    int vbc_n0;
    int vbc_n1;
    int vbc_n2;
    int vbc_n3;

    double vbc_val_x0;
    double vbc_val_x1;
    double vbc_val_y0;
    double vbc_val_y1;
    double vbc_val_z0;
    double vbc_val_z1;
    double vbc_val_n0;
    double vbc_val_n1;
    double vbc_val_n2;
    double vbc_val_n3;

    double bottom_shear_zone_thickness;

    double vbc_val_division_x0_min;
    double vbc_val_division_x0_max;
    double vbc_val_division_x1_min;
    double vbc_val_division_x1_max;

    double vbc_val_x0_ratio0;
    double vbc_val_x0_ratio1;
    double vbc_val_x0_ratio2;
    double vbc_val_x0_ratio3;
    double vbc_val_x1_ratio0;
    double vbc_val_x1_ratio1;
    double vbc_val_x1_ratio2;
    double vbc_val_x1_ratio3;

    int num_vbc_period_x0;
    int num_vbc_period_x1;

    double_vec vbc_period_x0_time_in_yr;
    double_vec vbc_period_x1_time_in_yr;

    double_vec vbc_period_x0_ratio;
    double_vec vbc_period_x1_ratio;

    double vbc_val_z1_loading_period;

    // General stress (Neumann) bcs 
    int stress_bc_x0;
    int stress_bc_x1;
    int stress_bc_y0;
    int stress_bc_y1;
    int stress_bc_z0;
    int stress_bc_z1;

    // hyrdaulic bouncdary
    int hbc_x0;
    int hbc_x1;
    int hbc_y0;
    int hbc_y1;
    int hbc_z0;
    int hbc_z1;

    double stress_val_x0;
    double stress_val_x1;
    double stress_val_y0;
    double stress_val_y1;
    double stress_val_z0;
    double stress_val_z1;
};

struct IC {
    int mattype_option;
    int num_mattype_layers;
    int_vec layer_mattypes;
    double_vec mattype_layer_depths;

    int weakzone_option;
    bool is_restarting_weakzone;
    double weakzone_plstrain;
    double weakzone_azimuth;
    double weakzone_inclination;
    double weakzone_halfwidth;
    double weakzone_y_min;
    double weakzone_y_max;
    double weakzone_depth_min;
    double weakzone_depth_max;
    double weakzone_xcenter;
    double weakzone_ycenter;
    double weakzone_zcenter;
    double weakzone_xsemi_axis;
    double weakzone_ysemi_axis;
    double weakzone_zsemi_axis;
    double weakzone_standard_deviation;

    int temperature_option;
    std::string Temp_filename;
    std::string Nodes_filename;
    std::string Connectivity_filename;
    double oceanic_plate_age_in_yr;
    double continental_plate_age_in_yr;
    double radiogenic_crustal_thickness;
    double radiogenic_folding_depth;
    double radiogenic_heating_of_crust;
    double lithospheric_thickness;
    int nhlayer;
    double_vec radiogenic_heat_boundry;
    int_vec radiogenic_heat_mat_in_layer;

    double isostasy_adjustment_time_in_yr;

    double excess_pore_pressure;
    bool has_body_force_adjustment;
};

struct Mat {
    int rheol_type;
    int phase_change_option;
    int nmat;
    int mattype_mantle;
    int mattype_depleted_mantle;
    int mattype_partial_melting_mantle;
    int mattype_crust;
    int mattype_sed;
    int mattype_oceanic_crust;
    double convert_rate_oceanic_crust;

    bool is_plane_strain;
    double visc_min;
    double visc_max;
    double tension_max;
    double therm_diff_max;

    double_vec rho0;
    double_vec alpha;

    double_vec bulk_modulus;
    double_vec shear_modulus;

    double_vec visc_exponent;
    double_vec visc_coefficient;
    double_vec visc_activation_energy;
    double_vec visc_activation_volume;

    double_vec heat_capacity;
    double_vec therm_cond;
    double_vec radiogenic_heat_prod;

    // plastic parameters
    double_vec pls0, pls1;
    double_vec cohesion0, cohesion1;
    double_vec friction_angle0, friction_angle1;
    double_vec dilation_angle0, dilation_angle1;

    // hydraulic parameters
    double_vec porosity;
    double_vec hydraulic_perm;
    double_vec fluid_rho0;  // pore fluid density
    double_vec fluid_alpha; // pore fluid thermal expansivity
    double_vec fluid_bulk_modulus;  // pore fluid bulk modulus
    double_vec fluid_visc;  // pore fluid dynamic viscosity
    double_vec biot_coeff;  // Biot-Willis coefficient
    double_vec bulk_modulus_s;  // bulk modulus of solid grain (mineral)
  
    // rate-and-state friction parameters
    double_vec direct_a;
    double_vec evolution_b;
    double_vec characteristic_velocity;
    // double_vec static_friction_coefficient;

};

struct Time {
    int64_t remesh_time;
    int64_t output_time;
    int64_t start_time;
};

struct Markers {
    int init_marker_option;
    int markers_per_element;
    int min_num_markers_in_element;
    int replenishment_option;
    uint random_seed;
    double init_marker_spacing;
};

struct Debug {
    bool dt;
//    bool has_two_layers_for;
};

struct Param {
    Sim sim;
    Mesh mesh;
    Control control;
    BC bc;
    IC ic;
    Mat mat;
    Markers markers;
    Debug debug;
};

//
// Structures for surface processes
//
struct SurfaceInfo {

//    const double sec_year = 31556925.2;

    int efacet_top;
    int ntop;

    double base_level;
    double surf_diff;
    double diff_ratio_terrig;
    double diff_ratio_marine;
    double terrig_diffusivity;
    double terrig_dpeth_coeff;
    double depo_universal;
    double ero_rate;
    double max_surf_vel;

    double_vec *dh;
    double_vec *dh_oc;
    double_vec *src_locs;

    double_vec *total_dx;
    double_vec *total_slope;

    int_vec *top_nodes;
    int_vec *top_facet_elems;

    int_vec *landform_map;
    double_vec *drainage;

    double_vec *dhacc;
    double_vec *edvacc_surf;
    int_vec2D *node_and_elems;
    segment_t *elem_and_nodes;

    double_vec *dhacc_oc;
    double_vec *edhacc_oc;

    std::vector<double_vec> *fcenters;
    std::vector<double_vec> *normals;
    std::vector<double_vec> *dips;

    int_map arctop_facet_elems;
    int_map arctop_nodes;


    int ntops;
    int nbots;
    int_vec tops;
    int_vec coasts;
    int_vec bots;

    double_vec top_elev;
    double_vec bot_elev;

};

//
// Structures for model variables
//
class MatProps;
class MarkerSet;
struct Variables {
    double time;
    double dt;
    double dt_PT;
    double l2_residual;
    int steps;
    Time func_time;

    int nnode;
    int nelem;
    int nseg;
    int nx, ny, nz, ncell;

    double max_vbc_val;
    double max_global_vel_mag;
    double global_dt_min;
    double compensation_pressure;
    double bottom_temperature;

// #ifdef ATS
//     double vmax, hmin, dt_elastic, dt_min, vmax_shear_zone, CL_min;
// #endif    
//     double a0, b0, a1, b1, max_pls, number_plf, seismic_eff, S_E, K_E;

//     double_vec *MAX_shear, *CL, *dl_min, *maxv, *strain_energy, *kinetic_energy, *MAX_shear_0;
// #ifdef RS
//     double_vec *state1, *slip_velocity, *friction_coefficient, *RS_shear, *Failure_mode, avg_shear_stress, avg_vm, slip_area;
// #endif

    // These 5 arrays are allocated by external library
    array_t *coord;
    conn_t *connectivity;
    segment_t *segment;
    segflag_t *segflag;
    regattr_t *regattr;
    array_t *old_coord;
    conn_t *old_connectivity;
    regular_t *cell;


    uint_vec *bcflag;
    int_vec *bnodes[nbdrytypes];
    std::vector< std::pair<int,int> > *bfacets[nbdrytypes];
    array_t *bnormals;
    int vbc_types[nbdrytypes];
    int hbc_types[nbdrytypes_hydro];
    int stress_bc_types[nbdrytypes_hydro];
    double vbc_values[nbdrytypes];
    double stress_bc_values[nbdrytypes];
    double vbc_val_z1_loading_period;

    std::map<std::pair<int,int>, double*> edge_vectors;
    double_vec vbc_vertical_div_x0;
    double_vec vbc_vertical_div_x1;
    double_vec vbc_vertical_ratio_x0;
    double_vec vbc_vertical_ratio_x1;

    int_vec *top_elems;
//    int_vec2D *marker_in_elem;

    int_vec2D *support;

    double_vec *volume, *volume_old, *volume_n;
    double_vec *mass, *tmass;
    double_vec *hmass;
    double_vec *ymass; // Young's modulus for nodes
    double_vec *edvoldt;
    double_vec *temperature, *plstrain, *delta_plstrain;
    double_vec *stressyy, *dpressure, *viscosity;
    double_vec *old_mean_stress;
    double_vec *ntmp;
    double_vec *radiogenic_source;

    // For hyraulic proceses
    double_vec *fmass; // pore water mass
    double_vec *ppressure; // pore pressure
    double_vec *dppressure; // delta pore pressure
    double_vec *dppressure_zero; // delta pore pressure
    double_vec *fluid_source; // injection and pumping of pore water
    
    // For rate-and-state friction
    double_vec *dyn_fric_coeff;

    // For surface processes
    SurfaceInfo surfinfo;
    int_vec melt_markers;

    array_t *vel, *force, *coord0;
    array_t *force_residual;
    tensor_t *strain_rate, *strain, *stress;
    shapefn *shpdx, *shpdy, *shpdz; // gradient of shape function
    elem_cache *tmp_result;
    double_vec *tmp_result_sg;

    // tensor_t *stress_old;

    MatProps *mat;

    std::vector<MarkerSet*> markersets;
    int hydrous_marker_index;

    int_vec2D *elemmarkers; // for marksersets[0] (mattype markers)
    Array2D<int,1> *hydrous_elemmarkers; // for markersets[hydrous_marker_index] (hydrous markers)

    PhaseChange *phch;

    Variables()
    {
        vbc_vertical_div_x0.resize(4);
        vbc_vertical_div_x1.resize(4);
        vbc_vertical_ratio_x0.resize(4);
        vbc_vertical_ratio_x1.resize(4);
    }

};

#endif
