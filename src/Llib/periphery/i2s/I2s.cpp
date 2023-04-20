#define L_PRINTKX_DEBUG
#include "I2s.hpp"
#include "Llib/periphery/periphery.hpp"
#include <zephyr/sys/__assert.h>

static const char* printkx_title_str = "I2S";

int I2s::initOut(){
    if (_host_i2s_tx_dev_p != NULL) {PRINTKN_ERROR("No such device", -1); return ps_noSuchDevice;}
    
    int ret = device_is_ready(_host_i2s_tx_dev_p);
    if (ret == false) {PRINTKN_ERROR("Device not ready", ret); return ps_notReady; }

    _i2s_tx_cfg.word_size      = 24;
    _i2s_tx_cfg.channels       = 2;
    _i2s_tx_cfg.frame_clk_freq = 44100;
    _i2s_tx_cfg.format         = I2S_FMT_DATA_FORMAT_I2S;
    _i2s_tx_cfg.options        = I2S_OPT_BIT_CLK_MASTER | I2S_OPT_FRAME_CLK_MASTER;
    _i2s_tx_cfg.timeout        = SYS_FOREVER_MS;

    ret = i2s_configure(_host_i2s_tx_dev_p, I2S_DIR_TX, &_i2s_tx_cfg);
    if (ret != 0) {PRINTKN_ERROR("Device corfiguration error", ret); return ps_configError;}
    PRINTKN_INFO("Out stream successfully initialized", ret);
    return ps_ok;
}

void I2s::setOut(k_mem_slab& mem_slab){
    _i2s_tx_cfg.block_size = mem_slab.block_size; 
    _i2s_tx_cfg.mem_slab   = &mem_slab;
}

void I2s::set(const device* dev_p){
    __ASSERT_NO_MSG(dev_p  != NULL); _host_i2s_tx_dev_p = dev_p;
}

void I2s::setParams (params_t* params_p) {
    if(_host_i2s_tx_dev_p == NULL) {PRINTKN_ERROR("Device is not initialized", -1); return;}
    if(params_p->params_st_id != params_st_audio) {PRINTKN_ERROR("Not supported \"params\" type provided", -1); return;}
    audio_param_t* audio_param = (audio_param_t*)(params_p->params_st_p);
    _i2s_tx_cfg.word_size      = audio_param->sampleWidth;
    _i2s_tx_cfg.frame_clk_freq = audio_param->sampleRate;
    _i2s_tx_cfg.channels       = audio_param->numOfChannels;
    int ret = i2s_configure(_host_i2s_tx_dev_p, I2S_DIR_TX, &_i2s_tx_cfg);
    if (ret != 0) {PRINTKN_ERROR("New \"params\" are not applied", -1);}
}

void I2s::outClean(){
        void *slab_mem_block_tmp_p;
        int ret = k_mem_slab_alloc(_i2s_tx_cfg.mem_slab, &slab_mem_block_tmp_p, K_FOREVER);
        if (ret < 0) {PRINTKN_ERROR("Out outClean() memory slab acquisition error", ret);}

        memset(slab_mem_block_tmp_p, 0, _i2s_tx_cfg.block_size);

        ret = i2s_write(_host_i2s_tx_dev_p, slab_mem_block_tmp_p, _i2s_tx_cfg.block_size);
        if (ret != 0) {
            PRINTKN_ERROR("Out outClean() data DMA set errorr", ret);
            k_mem_slab_free(_i2s_tx_cfg.mem_slab, &slab_mem_block_tmp_p);
        }
}

void I2s::outOpen(){
    int ret = i2s_trigger(_host_i2s_tx_dev_p, I2S_DIR_TX, I2S_TRIGGER_START);
    if (ret != 0) PRINTKN_ERROR("Out trigger \"START\" failed with error", ret);
}

void I2s::output(void* data_p, size_t* size_p, size_t* accepted_size){
    size_t current_block_size = _i2s_tx_cfg.block_size;
    *accepted_size            = _i2s_tx_cfg.block_size;
    if (*size_p < _i2s_tx_cfg.block_size){
        current_block_size    = *size_p;
        *accepted_size        = *size_p;
    }
    
    if(current_block_size < _i2s_tx_cfg.block_size) return;
    void *slab_mem_block_tmp_p;
    int ret = k_mem_slab_alloc(_i2s_tx_cfg.mem_slab, &slab_mem_block_tmp_p, K_FOREVER);
    if (ret < 0) {PRINTKN_ERROR("Out output() memory slab acquisition error", ret);}

    memcpy(slab_mem_block_tmp_p, data_p, current_block_size);

    ret = i2s_write(_host_i2s_tx_dev_p, slab_mem_block_tmp_p, current_block_size);
    if (ret != 0) {
        PRINTKN_ERROR("Out output() data DMA set error", ret);
        k_mem_slab_free(_i2s_tx_cfg.mem_slab, &slab_mem_block_tmp_p);
    }
}

void I2s::outFlush(){
    int ret = i2s_trigger(_host_i2s_tx_dev_p, I2S_DIR_TX, I2S_TRIGGER_DRAIN);
    if (ret != 0) PRINTKN_ERROR("Out trigger \"DRAIN\" failed with error", ret);
}

void I2s::outClose(){
    if(outIsBusy()){
        int ret = i2s_trigger(_host_i2s_tx_dev_p, I2S_DIR_TX, I2S_TRIGGER_STOP);
        if (ret != 0) PRINTKN_ERROR("Out trigger \"STOP\" failed with error", ret);
    }
}

bool I2s::outIsBusy(){
    return (k_mem_slab_num_used_get(_i2s_tx_cfg.mem_slab) > 0);
}
