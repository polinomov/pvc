

#include "ginclude.glsl"

// Calcuate partitions[ndx].lod = 0;

const std::string cs_lod = cs_glversion + cs_const_val+ cs_struct_point + cs_structs + cs_structs_partition+
R""(
 precision mediump float;
 layout(local_size_x = 64,local_size_y =1) in;   
 layout(std430,binding = 0) buffer in1  {  GlobalParams globs; };
 layout(std430,binding = 1) buffer pp   {  Partition partitions[]; }; 
 layout(std430,binding = 2) buffer vv   {  mat4 World2View; };
 layout(std430,binding = 4) buffer dbg  {  float debugOut[]; }; 
 void main()                           
 {
    uint ndx = gl_GlobalInvocationID.x + gl_GlobalInvocationID.y*64;
    Partition part = partitions[ndx];
    partitions[ndx].lod = uint(globs.wrkLoad);

    vec4 vc = World2View  * vec4(part.cx, part.cy, part.cz, 1.0) ;
 
    if( (vc.z > 0.0) && (vc.z < 1.0) )
    {
        vec4 tt = vec4(part.cx + globs.camUpx * part.sz , part.cy + globs.camUpy * part.sz, part.cz + globs.camUpz * part.sz, 1.0);
        vec4 vb  =  World2View  * tt ;
        float xa = vc.x/vc.w;
        float ya = vc.y/vc.w;
        float xb = vb.x/vb.w;
        float yb = vb.y/vb.w;
        float ddx =xa- xb;
        float ddy =ya-yb;
        uint dd = uint( sqrt(ddx*ddx + ddy*ddy));
        partitions[ndx].lod = clamp( dd, 1, uint(globs.wrkLoad));
    } 
    // globs.px,globs.py,globs.pz - camera position in world;
    float dx = part.cx - globs.px;
    float dy = part.cy - globs.py;
    float dz = part.cz - globs.pz;

    float prd0 = dx*globs.norm[0] + dy*globs.norm[1] + dz*globs.norm[2];
    if(prd0 > part.sz) partitions[ndx].lod = 0;

    prd0 = dx*globs.norm[4] + dy*globs.norm[5] + dz*globs.norm[6];
    if(prd0 > part.sz) partitions[ndx].lod = 0;

    prd0 = dx*globs.norm[8] + dy*globs.norm[9] + dz*globs.norm[10];
    if(prd0 > part.sz) partitions[ndx].lod = 0;

    prd0 = dx*globs.norm[12] + dy*globs.norm[13] + dz*globs.norm[14];
    if(prd0 > part.sz) partitions[ndx].lod = 0;

    prd0 = dx*globs.norm[16] + dy*globs.norm[17] + dz*globs.norm[18];
    if(prd0 > part.sz) partitions[ndx].lod = 0;

    //debug
    //debugOut[0] = globs.norm[0];
    //debugOut[1] = globs.norm[1];
    //debugOut[2] = globs.norm[2];
 
 }       
)"";
