#include <iostream>
#include <cmath>
#include <limits>

#include "AAD22.h"
#include "Differentiator.h"

double F(double x, double y) {
    return -3 * cos(x * y) + y * (-x) * 239;
//    return x/x;
}

ADAI::AAD22 F_AAD22(ADAI::AAD22 &x, ADAI::AAD22 &y) {
    return -3 * cos(x * y) + y * (-x) * 239;

//    return x/x;

}

int main() {
    double x = 3;
    double y = 3;

    printf("f'_x_st3 = %f\n", ADAI::Differentiator<ADAI::WhichD::x, ADAI::DiffMethod::stencil3>(&F, x, y));
    printf("f'_x_st3Extra = %f\n", ADAI::Differentiator<ADAI::WhichD::x, ADAI::DiffMethod::stencil3Extra>(&F, x, y));
    printf("f'_x_st5 = %f\n", ADAI::Differentiator<ADAI::WhichD::x, ADAI::DiffMethod::stencil5>(&F, x, y));
    printf("f'_x_st5Extra = %f\n", ADAI::Differentiator<ADAI::WhichD::x, ADAI::DiffMethod::stencil5Extra>(&F, x, y));
    printf("f'_x_FwdAAD = %f\n\n", ADAI::Differentiator<ADAI::WhichD::x, ADAI::DiffMethod::FwdAAD>(&F_AAD22, x, y));

    printf("f'_y_st3 = %f\n", ADAI::Differentiator<ADAI::WhichD::y, ADAI::DiffMethod::stencil3>(&F, x, y));
    printf("f'_y_st3Extra = %f\n", ADAI::Differentiator<ADAI::WhichD::y, ADAI::DiffMethod::stencil3Extra>(&F, x, y));
    printf("f'_y_st5 = %f\n", ADAI::Differentiator<ADAI::WhichD::y, ADAI::DiffMethod::stencil5>(&F, x, y));
    printf("f'_y_st5Extra = %f\n", ADAI::Differentiator<ADAI::WhichD::y, ADAI::DiffMethod::stencil5Extra>(&F, x, y));
    printf("f'_y_FwdAAD = %f\n\n", ADAI::Differentiator<ADAI::WhichD::y, ADAI::DiffMethod::FwdAAD>(&F_AAD22, x, y));

    printf("f''_xx_st3 = %f\n", ADAI::Differentiator<ADAI::WhichD::xx, ADAI::DiffMethod::stencil3>(&F, x, y));
    printf("f''_xx_st3Extra = %f\n", ADAI::Differentiator<ADAI::WhichD::xx, ADAI::DiffMethod::stencil3Extra>(&F, x, y));
    printf("f''_xx_st5 = %f\n", ADAI::Differentiator<ADAI::WhichD::xx, ADAI::DiffMethod::stencil5>(&F, x, y));
    printf("f''_xx_st5Extra = %f\n", ADAI::Differentiator<ADAI::WhichD::xx, ADAI::DiffMethod::stencil5Extra>(&F, x, y));
    printf("f''_xx_FwdAAD = %f\n\n", ADAI::Differentiator<ADAI::WhichD::xx, ADAI::DiffMethod::FwdAAD>(&F_AAD22, x, y));

    printf("f''_yy_st3 = %f\n", ADAI::Differentiator<ADAI::WhichD::yy, ADAI::DiffMethod::stencil3>(&F, x, y));
    printf("f''_yy_st3Extra = %f\n", ADAI::Differentiator<ADAI::WhichD::yy, ADAI::DiffMethod::stencil3Extra>(&F, x, y));
    printf("f''_yy_st5 = %f\n", ADAI::Differentiator<ADAI::WhichD::yy, ADAI::DiffMethod::stencil5>(&F, x, y));
    printf("f''_yy_st5Extra = %f\n", ADAI::Differentiator<ADAI::WhichD::yy, ADAI::DiffMethod::stencil5Extra>(&F, x, y));
    printf("f''_yy_FwdAAD = %f\n\n", ADAI::Differentiator<ADAI::WhichD::yy, ADAI::DiffMethod::FwdAAD>(&F_AAD22, x, y));

    printf("f''_xy_st3 = %f\n", ADAI::Differentiator<ADAI::WhichD::xy, ADAI::DiffMethod::stencil3>(&F, x, y));
    printf("f''_xy_st3Extra = %f\n", ADAI::Differentiator<ADAI::WhichD::xy, ADAI::DiffMethod::stencil3Extra>(&F, x, y));
    printf("f''_xy_st5 = %f\n", ADAI::Differentiator<ADAI::WhichD::xy, ADAI::DiffMethod::stencil5>(&F, x, y));
    printf("f''_xy_st5Extra = %f\n", ADAI::Differentiator<ADAI::WhichD::xy, ADAI::DiffMethod::stencil5Extra>(&F, x, y));
    printf("f''_xy_FwdAAD = %f\n", ADAI::Differentiator<ADAI::WhichD::xy, ADAI::DiffMethod::FwdAAD>(&F_AAD22, x, y));

    return 0;
}
