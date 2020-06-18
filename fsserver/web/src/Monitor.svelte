<script>
    export let data = {}
</script>

<style>

    table {
        table-layout: fixed;
        width: 400px;
    }
    td {
        border: 5px solid #333333;
        text-align: center;
    }

    td.red {
        color: #AA0000;
    }

    td.green {
        color: #005500;
    }

</style>

<table> 
    <tr>
        <td>
            {data.blag || ''}
        </td>
        <td class="{ data.r > 0 ? 'red' : 'green' }">
            {data.r || ''}
        </td>
        <td>
            {data.con || ''}
        </td>

</table>
