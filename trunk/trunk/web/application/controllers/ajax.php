<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Ajax extends CI_Controller {

    public function __construct()
    {
        parent::__construct();
    }

    public function index()
    {
        $this->output->set_output("This is an AJAX endpoint!");
    }

    public function user_availability()
    {
        $this->load->model("users");
        $res = $this->users->is_username_available( $this->input->post("username") );
        if( $res )
            $this->output->set_output("OK");
        else    
            $this->output->set_output("NOT OK");
    }
}

/* End of file welcome.php */
/* Location: ./application/controllers/ajax.php */