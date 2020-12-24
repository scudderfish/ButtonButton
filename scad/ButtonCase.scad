include <BOSL/shapes.scad>


$fn=90;
wt=3.3;
module esp32() {
    color("green") translate([-100,-118.5,0])import("/home/dgs/Downloads/lora32&kit32_all.stl",convexity = 10);
}

module case(h=30) {
    
    intersection() {
                cuboid([68,68,h],fillet=8.5,edges=EDGE_FR_RT+EDGE_FR_LF+EDGE_BK_RT+EDGE_BK_LF);
    
    difference() {
        union(){
            difference(){
                cuboid([68,68,h],fillet=8.5,edges=EDGE_FR_RT+EDGE_FR_LF+EDGE_BK_RT+EDGE_BK_LF);
                translate([0,0,1.65])cuboid([68-wt,68-wt,h],fillet=8.5,edges=EDGE_FR_RT+EDGE_FR_LF+EDGE_BK_RT+EDGE_BK_LF);
            }
            translate([25.75,25.75,-(h/2)]) cylinder(h=h,d1=6,d2=10);
            translate([-25.75,-25.75,-(h/2)])cylinder(h=h,d1=6,d2=10);
            translate([25.75,-25.75,-(h/2)])cylinder(h=h,d1=6,d2=10);
            translate([-25.75,25.75,-(h/2)])cylinder(h=h,d1=6,d2=10);

            translate([-27.75,27.75,0])cuboid([10,10,h],fillet=5,edges=EDGE_FR_RT);
            translate([27.75,27.75,0])cuboid([10,10,h],fillet=5,edges=EDGE_FR_LF);
            translate([27.75,-27.75,0])cuboid([10,10,h],fillet=5,edges=EDGE_BK_LF);
            translate([-27.75,-27.75,0])cuboid([10,10,h],fillet=5,edges=EDGE_BK_RT);



            translate([33,-23,0]) rotate([0,0,0]) interior_fillet(l=h,r=8,orient=ORIENT_ZNEG);
            translate([33,23,0]) rotate([0,0,90]) interior_fillet(l=h,r=8,orient=ORIENT_ZNEG);
            translate([-33,23,0]) rotate([0,0,180]) interior_fillet(l=h,r=8,orient=ORIENT_ZNEG);
            translate([-33,-23,0]) rotate([0,0,270]) interior_fillet(l=h,r=8,orient=ORIENT_ZNEG);

            translate([-22.75,34,0]) rotate([0,0,270]) interior_fillet(l=h,r=8,orient=ORIENT_Z);
            translate([22.75,34,0]) rotate([0,0,180]) interior_fillet(l=h,r=8,orient=ORIENT_Z);
            translate([22.75,-34,0]) rotate([0,0,90]) interior_fillet(l=h,r=8,orient=ORIENT_Z);
            translate([-22.75,-34,0]) rotate([0,0,0]) interior_fillet(l=h,r=8,orient=ORIENT_Z);
            
            translate([31.5,0,0]) cuboid([5,60,h])
            translate([-32,0,0]) sparse_strut(h=h, strut=2,l=70-wt*4, thick=3);
            translate([0,32,0]) rotate([0,0,90]) sparse_strut(h=h, strut=2,l=70-wt*4, thick=3);
            translate([0,-32,0]) rotate([0,0,90]) sparse_strut(h=h, strut=2,l=70-wt*4, thick=3);
        }
        
        #translate([25.75,25.75,h/2-14]) cylinder(14,d=5.5);
        translate([-25.75,-25.75,h/2-14])cylinder(h=14,d=5.5);
        translate([25.75,-25.75,h/2-14])cylinder(h=14,d=5.5);
        translate([-25.75,25.75,h/2-14]) cylinder(h=14,d=5.5);

        translate([25.75,25.75,h/2]) downcyl(l=1,d2=6,d1=5);
        translate([-25.75,-25.75,h/2]) downcyl(l=1,d2=6,d1=5);
        translate([25.75,-25.75,h/2]) downcyl(l=1,d2=6,d1=5);
        translate([-25.75,25.75,h/2]) downcyl(l=1,d2=6,d1=5);

        translate([32,3,-4]) cuboid([10,33.5,20.5]);
        translate([31,-30,-4]) cuboid([10,10,10]);
        translate([28,-24,-4]) cuboid([6,10,26]);
    }
    }
}
module switchBody() {
    cuboid([30,30,25]);
}

module lipo() {
    cuboid([42,25,10.5]);
}
//translate([27,3,-4]) rotate([-90,0,-90]) esp32();
//lipo();
case(h=40);