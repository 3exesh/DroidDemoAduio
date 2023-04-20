/**
  ******************************************************************************
  * @file           : I2s.cpp
  * @brief          :
  * @author         : Datsii Vladisalav
  * @date           :
  ******************************************************************************
  * @attention
  *
  *  Droid Demo Adudio - nRF52840DK 
  *
  ******************************************************************************
  */

#ifndef I2S_HPP_
#define I2S_HPP_
#include <zephyr/kernel.h>
#include <zephyr/drivers/i2s.h>
#include "Llib/common/interfaces/DataStream.hpp"
#include "Llib/common/params.hpp"


class I2s : public OutDataStream{
public:
    //Base:
    void connect    (InDataStream& istream) {_istream_p = &istream;}
    void setOut     (k_mem_slab&   mem_slab);
    void set        (const device* dev_p);
    int  initOut    ();
    int  initIn     ();

    //OutDataStream

    void outOpen    ()                                                    override;
    void outClose   ()                                                    override;
    void outClean   ()                                                    override;
    void outFlush   ()                                                    override;
    bool outIsBusy  ()                                                    override;
    void output     (void* data_p, size_t* size_p, size_t* accepted_size) override;
    void setParams  (params_t* params_p)                                  override;
private:
             InDataStream*  _istream_p          = NULL;
       const device*        _host_i2s_tx_dev_p  = NULL;
             i2s_config     _i2s_tx_cfg;
};

#endif //I2S_HPP_